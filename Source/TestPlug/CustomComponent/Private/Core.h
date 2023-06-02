#pragma once
#include "MeshMaterialShader.h"
#include "MyMeshComponent.h"

struct FCustomMeshVertexFactory;
class FCustomMeshSceneProxy;
class FCustomMeshVertexFactoryShaderParameters;
class UMyMeshComponent;
struct FMyMeshSection;

struct FCustomMeshVertexFactory : FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FCustomMeshVertexFactory);

	FCustomMeshVertexFactory(ERHIFeatureLevel::Type InFeatureLevel)
		: FLocalVertexFactory(InFeatureLevel, "FCustomMeshVertexFactory"), SceneProxy(nullptr), SectionIndex(0)
	{}

	virtual void InitRHI() override;
	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters,FShaderCompilerEnvironment& OutEnv);
	void SetSceneProxy(const FCustomMeshSceneProxy* Proxy) { SceneProxy = Proxy; }
	const FCustomMeshSceneProxy* GetSceneProxy() const { return SceneProxy; }
	uint32 GetSectionIndex() const{return SectionIndex;}
	void SetSectionIndex(const uint32 _SectionIndex){this->SectionIndex = _SectionIndex;}
private:
	const FCustomMeshSceneProxy* SceneProxy;
	uint32 SectionIndex;
	friend class FCustomMeshVertexFactoryShaderParameters;
};

class FCustomMeshSectionProxy
{
public:
	UMaterialInterface* Material;
	FRawStaticIndexBuffer IndexBuffer;
	FCustomMeshVertexFactory VertexFactory;
	bool bVisible;
	uint32_t MaxVertexIndex;
	FCustomMeshSectionProxy(ERHIFeatureLevel::Type InFeatureLevel);
};

class FCustomMeshSceneProxy final : public FPrimitiveSceneProxy
{
public:
	virtual SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<SIZE_T>(&UniquePointer);
	}

	TSharedPtr<FCustomMeshSectionProxy> CreateSectionProxy(int SectionIndex,const FMyMeshSection& Element,const UMyMeshComponent& Component) const;
	const FShaderResourceViewRHIRef& GetPreTransformSRV() const { return PreTransformSRV; }
	void CreatePreSectionTransformSRV();
	FCustomMeshSceneProxy(UMyMeshComponent* Component);
	virtual ~FCustomMeshSceneProxy() override;

	void SetSectionVisibility_RenderThread(int SectionIndex,bool bVisible);
	void SetSectionPreTransform_RenderThread(int SectionIndex,const FMatrix& PreTransform);
	void UpdateSectionPreTransformRSV_RenderThread() const;
	virtual uint32 GetMemoryFootprint( void ) const override { return( sizeof( *this ) + GetAllocatedSize() ); }
	uint32 GetAllocatedSize( void ) const { return( FPrimitiveSceneProxy::GetAllocatedSize() + Sections.GetAllocatedSize() ); }
	virtual bool CanBeOccluded() const override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily,
		uint32 VisibilityMap, FMeshElementCollector& Collector) const override;

private:
	FMaterialRelevance MaterialRelevance;
	TArray<TSharedPtr<FCustomMeshSectionProxy>> Sections;
	TResourceArray<FMatrix> PreTransforms;
	FStructuredBufferRHIRef PreTransformsSB;
	FShaderResourceViewRHIRef PreTransformSRV;
};

class FCustomMeshVertexFactoryShaderParameters : public FVertexFactoryShaderParameters
{
	DECLARE_TYPE_LAYOUT(FCustomMeshVertexFactoryShaderParameters, NonVirtual);
public:
	void Bind(const FShaderParameterMap& ParameterMap);
	void GetElementShaderBindings(
		const class FSceneInterface* Scene,
		const FSceneView* View,
		const FMeshMaterialShader* Shader,
		const EVertexInputStreamType InputStreamType,
		ERHIFeatureLevel::Type FeatureLevel,
		const FVertexFactory* VertexFactory,
		const FMeshBatchElement& BatchElement,
		class FMeshDrawSingleShaderBindings& ShaderBindings,
		FVertexInputStreamArray& VertexStreams) const;

	LAYOUT_FIELD(FShaderResourceParameter,SectionPreTransformSRV);
	LAYOUT_FIELD(FShaderParameter,SectionPreTransformIndex);
};
