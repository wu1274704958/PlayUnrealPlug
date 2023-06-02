#if 1

#include "Core.h"
#include "MyMeshComponent.h"



void FCustomMeshVertexFactory::InitRHI()
{
	FLocalVertexFactory::InitRHI();
}

bool FCustomMeshVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters)
{
	return FLocalVertexFactory::ShouldCompilePermutation(Parameters);
}

void FCustomMeshVertexFactory::ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters,
	FShaderCompilerEnvironment& OutEnv)
{
	FLocalVertexFactory::ModifyCompilationEnvironment(Parameters,OutEnv);
}

void InitVertexFactoryData(FCustomMeshVertexFactory& VertexFactory,FStaticMeshVertexBuffers& VertexBuffers,int32_t LightMapCoordinateIndex)
{
	ENQUEUE_RENDER_COMMAND(StaticMeshVertexBuffersInit)(
		[&](FRHICommandListImmediate& RHICmdList)
		{
			FLocalVertexFactory::FDataType Data;
			VertexBuffers.PositionVertexBuffer.BindPositionVertexBuffer(&VertexFactory, Data);
			VertexBuffers.StaticMeshVertexBuffer.BindTangentVertexBuffer(&VertexFactory, Data);
			VertexBuffers.StaticMeshVertexBuffer.BindPackedTexCoordVertexBuffer(&VertexFactory, Data);
			LightMapCoordinateIndex = LightMapCoordinateIndex < (int32)VertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords() ?
				LightMapCoordinateIndex : (int32)VertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords() - 1;
			if(LightMapCoordinateIndex >= 0)
				VertexBuffers.StaticMeshVertexBuffer.BindLightMapVertexBuffer(&VertexFactory, Data, LightMapCoordinateIndex);
			VertexBuffers.ColorVertexBuffer.BindColorVertexBuffer(&VertexFactory, Data);

			Data.LODLightmapDataIndex = 0;
			VertexFactory.SetData(Data);
			VertexFactory.InitResource();
		});
}


FCustomMeshSectionProxy::FCustomMeshSectionProxy(ERHIFeatureLevel::Type InFeatureLevel) :
	Material(nullptr),VertexFactory(InFeatureLevel),bVisible(true),MaxVertexIndex(0)
{
	
}

FCustomMeshSceneProxy::FCustomMeshSceneProxy(UMyMeshComponent* Component) : FPrimitiveSceneProxy(Component),
                                                                            MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
{
	Sections.AddDefaulted(Component->Sections.Num());
	for(int i = 0;i < Component->Sections.Num();i++)
	{
		Sections[i] = CreateSectionProxy(i,Component->Sections[i],*Component);
	}
}
TSharedPtr<FCustomMeshSectionProxy> FCustomMeshSceneProxy::CreateSectionProxy(int SectionIndex,const FMyMeshSection& Section,const UMyMeshComponent& Component) const
{
	TSharedPtr<FCustomMeshSectionProxy> Proxy = MakeShared<FCustomMeshSectionProxy>(GetScene().GetFeatureLevel());
	Proxy->bVisible = Section.bVisible;
	Proxy->Material = Component.GetMaterial(SectionIndex);
	if(Proxy->Material == nullptr)
		Proxy-> Material = UMaterial::GetDefaultMaterial(MD_Surface);
	auto& LodResource = Section.StaticMesh->GetRenderData()->LODResources[0];
	InitVertexFactoryData(Proxy->VertexFactory,LodResource.VertexBuffers,Section.StaticMesh->GetLightMapCoordinateIndex());
	{
		TArray<uint32_t> TmpIndices;
		LodResource.IndexBuffer.GetCopy(TmpIndices);
		Proxy->IndexBuffer.AppendIndices(TmpIndices.GetData(),TmpIndices.Num());
		BeginInitResource(&Proxy->IndexBuffer);
	}
	Proxy->MaxVertexIndex = LodResource.VertexBuffers.PositionVertexBuffer.GetNumVertices() - 1;
	return Proxy;
}

FCustomMeshSceneProxy::~FCustomMeshSceneProxy()
{
	for(const auto& Section : Sections)
	{
		Section->VertexFactory.ReleaseResource();
		Section->IndexBuffer.ReleaseResource();
	}
	Sections.Reset();
}

void FCustomMeshSceneProxy::SetSectionVisibility_RenderThread(int SectionIndex, bool bVisible)
{
	check(IsInRenderingThread());
	if(SectionIndex < Sections.Num() && Sections[SectionIndex].IsValid())
	{
		Sections[SectionIndex]->bVisible = bVisible;
	}
}

bool FCustomMeshSceneProxy::CanBeOccluded() const
{
	return !MaterialRelevance.bDisableDepthTest;
}

FPrimitiveViewRelevance FCustomMeshSceneProxy::GetViewRelevance(const FSceneView* View) const
{
	FPrimitiveViewRelevance Result;
	Result.bDrawRelevance = IsShown(View);
	Result.bShadowRelevance = IsShadowCast(View);
	Result.bDynamicRelevance = true;
	Result.bRenderInMainPass = ShouldRenderInMainPass();
	Result.bUsesLightingChannels = GetLightingChannelMask() != GetDefaultLightingChannelMask();
	Result.bRenderCustomDepth = ShouldRenderCustomDepth();
	Result.bTranslucentSelfShadow = bCastVolumetricTranslucentShadow;
	MaterialRelevance.SetPrimitiveViewRelevance(Result);
	Result.bVelocityRelevance = IsMovable() && Result.bOpaque && Result.bRenderInMainPass;
	return Result;
}

void FCustomMeshSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views,
	const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const
{
	const bool bWireframe = AllowDebugViewmodes() && ViewFamily.EngineShowFlags.Wireframe;

	FColoredMaterialRenderProxy* WireframeMaterialInstance = nullptr;
	if(bWireframe)
	{
		WireframeMaterialInstance = new FColoredMaterialRenderProxy(GEngine->WireframeMaterial ? GEngine->WireframeMaterial->GetRenderProxy() : nullptr,
			FLinearColor(0.f,0.5f,1.f));
		Collector.RegisterOneFrameMaterialProxy(WireframeMaterialInstance);
	}

	for(const auto& Section : Sections)
	{
		if(Section.IsValid() && Section->bVisible)
		{
			const FMaterialRenderProxy* MaterialProxy = bWireframe ? WireframeMaterialInstance : Section->Material->GetRenderProxy();
			for(int i = 0 ;i < Views.Num();i++)
			{
				if(VisibilityMap & (1 << i))
				{
					auto View = Views[i];
					auto& MeshBatch = Collector.AllocateMesh();
					auto& BatchElement = MeshBatch.Elements[0];
					BatchElement.IndexBuffer = &Section->IndexBuffer;

					MeshBatch.bWireframe = bWireframe;
					MeshBatch.VertexFactory = &Section->VertexFactory;
					MeshBatch.MaterialRenderProxy = MaterialProxy;

					bool bHasPreComputedVolumetricLightMap;
					FMatrix PreviousLocalToWorld;
					int32 SingleCaptureIndex;
					bool bOutputVelocity;
					GetScene().GetPrimitiveUniformShaderParameters_RenderThread(GetPrimitiveSceneInfo(),bHasPreComputedVolumetricLightMap,PreviousLocalToWorld,SingleCaptureIndex,bOutputVelocity);
					auto& DynamicPrimitiveUniformBuffer = Collector.AllocateOneFrameResource<FDynamicPrimitiveUniformBuffer>();
					DynamicPrimitiveUniformBuffer.Set(GetLocalToWorld(),PreviousLocalToWorld,GetBounds(),GetLocalBounds(),
						true,bHasPreComputedVolumetricLightMap,DrawsVelocity(),bOutputVelocity);
					BatchElement.PrimitiveUniformBufferResource = &DynamicPrimitiveUniformBuffer.UniformBuffer;
					BatchElement.PrimitiveIdMode = EPrimitiveIdMode::PrimID_DynamicPrimitiveShaderData;

					//additional data
					BatchElement.FirstIndex = 0;
					BatchElement.NumPrimitives = Section->IndexBuffer.GetNumIndices() / 3;
					BatchElement.MinVertexIndex = 0;
					BatchElement.MaxVertexIndex = Section->MaxVertexIndex;

					MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
					MeshBatch.Type = PT_TriangleList;
					MeshBatch.DepthPriorityGroup = SDPG_World;
					MeshBatch.bCanApplyViewModeOverrides = false;
					
					Collector.AddMesh(i,MeshBatch);
				}
			}
		}
	}
}

void FCustomMeshVertexFactoryShaderParameters::GetElementShaderBindings(const FSceneInterface* Scene,
	const FSceneView* View, const FMeshMaterialShader* Shader, const EVertexInputStreamType InputStreamType,
	ERHIFeatureLevel::Type FeatureLevel, const FVertexFactory* VertexFactory, const FMeshBatchElement& BatchElement,
	FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams) const
{
	const FRHIUniformBuffer* VertexFactoryUniformBuffer = static_cast<FRHIUniformBuffer*>(BatchElement.VertexFactoryUserData);
	const auto* LocalVertexFactory = static_cast<const FLocalVertexFactory*>(VertexFactory);
	if(LocalVertexFactory->SupportsManualVertexFetch(FeatureLevel) || UseGPUScene(GMaxRHIShaderPlatform,FeatureLevel))
	{
		if(!VertexFactoryUniformBuffer)
			VertexFactoryUniformBuffer = LocalVertexFactory->GetUniformBuffer();
		ShaderBindings.Add(Shader->GetUniformBufferParameter<FLocalVertexFactoryUniformShaderParameters>(),VertexFactoryUniformBuffer);
	}
	if(BatchElement.bUserDataIsColorVertexBuffer)
	{
		auto OverrideColorVertextBuffer = static_cast<const FColorVertexBuffer*>(BatchElement.UserData);
		check(OverrideColorVertextBuffer);

		if(!LocalVertexFactory->SupportsManualVertexFetch(FeatureLevel))
			LocalVertexFactory->GetColorOverrideStream(OverrideColorVertextBuffer,VertexStreams);
	}
	
}


IMPLEMENT_TYPE_LAYOUT(FCustomMeshVertexFactoryShaderParameters);

IMPLEMENT_VERTEX_FACTORY_PARAMETER_TYPE(FCustomMeshVertexFactory,SF_Vertex,FCustomMeshVertexFactoryShaderParameters);

IMPLEMENT_VERTEX_FACTORY_TYPE_EX(FCustomMeshVertexFactory, "/Shaders/CustomMeshVertexFactory.ush", true, true, true,
								 true, true, true, true);

#endif
