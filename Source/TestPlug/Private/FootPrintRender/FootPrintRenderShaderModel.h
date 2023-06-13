#pragma once

class FootPrintRenderShader : public FGlobalShader
{
	DECLARE_INLINE_TYPE_LAYOUT(FootPrintRenderShader, NonVirtual);
public:
	FootPrintRenderShader() = default;

	explicit FootPrintRenderShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
	}

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
	
};
