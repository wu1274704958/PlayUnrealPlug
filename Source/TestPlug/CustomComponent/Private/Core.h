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
		: FLocalVertexFactory(InFeatureLevel, "FCustomMeshVertexFactory"),SceneProxy(nullptr)
	{
		bSupportsManualVertexFetch = false;
	}

	virtual void InitRHI() override;
	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters,FShaderCompilerEnvironment& OutEnv);
	inline void	SetSceneProxy(FCustomMeshSceneProxy* Proxy) { SceneProxy = Proxy; }
private:
	FCustomMeshSceneProxy* SceneProxy;
	friend class FCustomMeshVertexFactoryShaderParameters;
};

static void InitOrUpdateResource(FRenderResource& Resource);

class FCustomMeshSctionProxy
{
public:
	UMaterialInterface* Material;
	FRawStaticIndexBuffer IndexBuffer;
	FCustomMeshVertexFactory VertexFactory;
	bool bVisible;
	uint32_t MaxVertexIndex;
	FCustomMeshSctionProxy(ERHIFeatureLevel::Type InFeatureLevel);
};

class FCustomMeshSceneProxy final : public FPrimitiveSceneProxy
{
public:
	virtual SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<SIZE_T>(&UniquePointer);
	}

	TSharedPtr<FCustomMeshSctionProxy> CreateSectionProxy(int SectionIndex,const FMyMeshSection& Element,const UMyMeshComponent& Component) const;
	FCustomMeshSceneProxy(UMyMeshComponent* Component);
	virtual ~FCustomMeshSceneProxy() override;

private:
	FMaterialRelevance MaterialRelevance;
	TArray<TSharedPtr<FCustomMeshSctionProxy>> Sections;
};