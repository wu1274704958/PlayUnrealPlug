#include "FootPrintRenderShaderModel.h"

bool FootPrintRenderShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
	return IsFeatureLevelSupported(	Parameters.Platform, ERHIFeatureLevel::SM5);
}

void FootPrintRenderShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
}
