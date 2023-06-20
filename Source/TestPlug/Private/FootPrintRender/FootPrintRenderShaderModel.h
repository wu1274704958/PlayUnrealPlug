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

	explicit CopyTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
	template <typename TShaderRHIParamRef>
	void SetParameters(FRHICommandListImmediate& RHICmdList,const TShaderRHIParamRef ShaderRHI,FVector2D InOffset,FTexture* InTexture)
	{
		SetShaderValue(RHICmdList, ShaderRHI, Offset, InOffset);
		SetTextureParameter(RHICmdList, ShaderRHI, Texture,Sampler,InTexture);
	}

	LAYOUT_FIELD(FShaderResourceParameter, Texture);
	LAYOUT_FIELD(FShaderResourceParameter, Sampler);
	LAYOUT_FIELD(FShaderParameter,Offset);
};

DECLARE_SHADER_BY_BASE(VS, CopyTextureShader);
DECLARE_SHADER_BY_BASE(PS,CopyTextureShader);

class DrawTextureShader : public FGlobalShader
{
	DECLARE_INLINE_TYPE_LAYOUT(DrawTextureShader, NonVirtual);
public:
	DrawTextureShader() = default;
	explicit DrawTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer);
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);
	template <typename TShaderRHIParamRef>
	void SetParameters(FRHICommandListImmediate& RHICmdList,const TShaderRHIParamRef ShaderRHI,FVector PosAndRotate,FVector4 InSizeAndPivot,FTexture* InTexture)
	{
		SetShaderValue(RHICmdList, ShaderRHI, PositionAndRotate, PosAndRotate);
		SetShaderValue(RHICmdList, ShaderRHI, SizeAndPivot, InSizeAndPivot);
		SetTextureParameter(RHICmdList, ShaderRHI, Texture,Sampler,InTexture);
	}
	LAYOUT_FIELD(FShaderResourceParameter, Texture);
	LAYOUT_FIELD(FShaderResourceParameter, Sampler);
	LAYOUT_FIELD(FShaderParameter,PositionAndRotate);
	LAYOUT_FIELD(FShaderParameter,SizeAndPivot);
};

DECLARE_SHADER_BY_BASE(VS, DrawTextureShader);
DECLARE_SHADER_BY_BASE(PS, DrawTextureShader);
void DrawCopyTexture_GameThread(FVector2D Offset,FTexture* InTexture,FTextureRenderTargetResource* OutTextureRenderTargetResource,ERHIFeatureLevel::Type FeatureLevel);
void DrawTexture_GameThread(FVector PosAndRotate,FVector4 InSizeAndPivot,FTexture* InTexture,FTextureRenderTargetResource* OutTextureRenderTargetResource,ERHIFeatureLevel::Type FeatureLevel);