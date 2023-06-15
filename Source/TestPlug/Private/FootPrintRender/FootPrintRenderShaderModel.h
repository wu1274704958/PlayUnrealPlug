#pragma once

#define DECLARE_SHADER_BY_BASE(STAGE,BASE) \
class BASE##STAGE : public BASE	\
{		\
	DECLARE_SHADER_TYPE(BASE##STAGE, Global);	\
	public:		\
	BASE##STAGE() = default;	\
	explicit BASE##STAGE(const ShaderMetaType::CompiledShaderInitializerType& Initializer)	\
		: BASE(Initializer)	\
	{	\
	}	\
};

class CopyTextureShader : public FGlobalShader
{
	DECLARE_INLINE_TYPE_LAYOUT(CopyTextureShader, NonVirtual);
public:
	CopyTextureShader() = default;

	explicit CopyTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		Offset.Bind(Initializer.ParameterMap, TEXT("Offset"));
		Texture.Bind(Initializer.ParameterMap, TEXT("Texture"));
		Sampler.Bind(Initializer.ParameterMap, TEXT("Sampler"));
	}

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
	template <typename TShaderRHIParamRef>
	void SetParameters(FRHICommandListImmediate& RHICmdList,const TShaderRHIParamRef ShaderRHI,FVector2D Offset,FTexture* InTexture)
	{
		SetShaderValue(RHICmdList, ShaderRHI, Offset);
		SetTextureParameter(RHICmdList, ShaderRHI, Texture,Sampler,InTexture);
	}

	LAYOUT_FIELD(FShaderResourceParameter, Texture);
	LAYOUT_FIELD(FShaderResourceParameter, Sampler);
	LAYOUT_FIELD(FShaderParameter,Offset);
};

DECLARE_SHADER_BY_BASE(VS, CopyTextureShader);
DECLARE_SHADER_BY_BASE(PS,CopyTextureShader);

void DrawCopyTexture_GameThread(FVector2D Offset,const FTexture* InTexture,FTextureRenderTargetResource* OutTextureRenderTargetResource);
