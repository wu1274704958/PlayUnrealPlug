#pragma once
#include "MeshMaterialShader.h"
#include "MyMeshComponent.h"

struct FCustomMeshVertexFactory;
class FCustomMeshSceneProxy;
class FCustomMeshVertexFactoryShaderParameters;

struct FCustomMeshVertexFactory : FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FCustomMeshVertexFactory);

	FCustomMeshVertexFactory(ERHIFeatureLevel::Type InFeatureLevel, const char* InDebugName)
		: FLocalVertexFactory(InFeatureLevel, InDebugName),SceneProxy(nullptr)
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

class FCustomMeshSceneProxy final : public FPrimitiveSceneProxy
{
public:
	virtual SIZE_T GetTypeHash() const override
	{
		static size_t UniquePointer;
		return reinterpret_cast<SIZE_T>(&UniquePointer);
	}
	FCustomMeshSceneProxy(UMyMeshComponent* Component) : FPrimitiveSceneProxy(Component),
	MaterialRelevance(Component->GetMaterialRelevance(GetScene().GetFeatureLevel()))
	{
		
	}

private:
	FMaterialRelevance MaterialRelevance;
};