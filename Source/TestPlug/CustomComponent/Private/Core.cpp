#if 1

#include "Core.h"


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

#endif