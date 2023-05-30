#if 1

#include "Core.h"
#include "MyMeshComponent.h"

IMPLEMENT_VERTEX_FACTORY_TYPE_EX(FCustomMeshVertexFactory,"/Shaders/CustomMeshVertexFactory.ush",true,true,true,true,true,true,true);

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

void InitOrUpdateResource(FRenderResource& Resource)
{
	if(Resource.IsInitialized())
		Resource.UpdateRHI();
	else
		Resource.InitResource();
}

void InitVertexFactoryData(FCustomMeshVertexFactory& VertexFactory,const FStaticMeshVertexBuffers& VertexBuffers,int32_t LightMapCoordinateIndex)
{
	ENQUEUE_RENDER_COMMAND(StaticMeshVertexBuffersInit)(
		[&](FRHICommandListImmediate& RHICmdList)
		{
			FLocalVertexFactory::FDataType Data;
			VertexBuffers.PositionVertexBuffer.BindPositionVertexBuffer(&VertexFactory, Data);
			VertexBuffers.StaticMeshVertexBuffer.BindTangentVertexBuffer(&VertexFactory, Data);
			VertexBuffers.StaticMeshVertexBuffer.BindPackedTexCoordVertexBuffer(&VertexFactory, Data);
			VertexBuffers.StaticMeshVertexBuffer.BindLightMapVertexBuffer(&VertexFactory, Data, LightMapCoordinateIndex);
			VertexBuffers.ColorVertexBuffer.BindColorVertexBuffer(&VertexFactory, Data);

			Data.LODLightmapDataIndex = 0;
			VertexFactory.SetData(Data);
			VertexFactory.InitResource();
		});
}


FCustomMeshSctionProxy::FCustomMeshSctionProxy(ERHIFeatureLevel::Type InFeatureLevel) :
	Material(nullptr),bVisible(true),MaxVertexIndex(0),VertexFactory(InFeatureLevel)
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
TSharedPtr<FCustomMeshSctionProxy> FCustomMeshSceneProxy::CreateSectionProxy(int SectionIndex,const FMyMeshSection& Element,const UMyMeshComponent& Component) const
{
	TSharedPtr<FCustomMeshSctionProxy> Proxy = MakeShared<FCustomMeshSctionProxy>(GetScene().GetFeatureLevel());
	Proxy->bVisible = Element.bVisible;
	Proxy->Material = Component.GetMaterial(SectionIndex);
	const auto& LodResource = Element.StaticMesh->GetRenderData()->LODResources[0];
	InitVertexFactoryData(Proxy->VertexFactory,LodResource.VertexBuffers,Element.StaticMesh->GetLightMapCoordinateIndex());
	{
		TArray<uint32_t> TmpIndices;
		LodResource.IndexBuffer.GetCopy(TmpIndices);
		Proxy->IndexBuffer.AppendIndices(TmpIndices.GetData(),TmpIndices.Num());
		BeginInitResource(&Proxy->IndexBuffer);
	}
	
	return Proxy;
}

FCustomMeshSceneProxy::~FCustomMeshSceneProxy()
{
	Sections.Reset();
}

#endif
