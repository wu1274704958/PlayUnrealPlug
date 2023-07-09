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
	void SetParameters(FRHICommandListImmediate& RHICmdList,const TShaderRHIParamRef ShaderRHI,FVector2D InOffset,FTexture* InTexture,
		FLinearColor InSubtractColor = FLinearColor(0.0f,0.0f,0.0f,0.0f))
	{
		SetShaderValue(RHICmdList, ShaderRHI, Offset, InOffset);
		SetTextureParameter(RHICmdList, ShaderRHI, Texture,Sampler,InTexture);
		SetShaderValue(RHICmdList, ShaderRHI, SubtractColor,InSubtractColor);
	}

	LAYOUT_FIELD(FShaderResourceParameter, Texture);
	LAYOUT_FIELD(FShaderResourceParameter, Sampler);
	LAYOUT_FIELD(FShaderParameter,Offset);
	LAYOUT_FIELD(FShaderParameter,SubtractColor);
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
	void SetParameters(FRHICommandListImmediate& RHICmdList,const TShaderRHIParamRef ShaderRHI,FVector PosAndRotate,FVector4 InSizeAndPivot,
		FTexture* InDepthTexture,
		FTexture* InSdfTexture,float zeroPlaneDepth)
	{
		SetShaderValue(RHICmdList, ShaderRHI, PositionAndRotate, PosAndRotate);
		SetShaderValue(RHICmdList, ShaderRHI, SizeAndPivot, InSizeAndPivot);
		SetTextureParameter(RHICmdList, ShaderRHI,DepthTexture,DepthSampler,InDepthTexture);
		SetTextureParameter(RHICmdList,ShaderRHI,SdfTexture,SdfSampler,InSdfTexture);
		SetShaderValue(RHICmdList, ShaderRHI, ZeroPlaneDepth, zeroPlaneDepth);
	}
	LAYOUT_FIELD(FShaderResourceParameter, DepthTexture);
	LAYOUT_FIELD(FShaderResourceParameter, DepthSampler);
	LAYOUT_FIELD(FShaderResourceParameter, SdfTexture);
	LAYOUT_FIELD(FShaderResourceParameter, SdfSampler);
	LAYOUT_FIELD(FShaderParameter,PositionAndRotate);
	LAYOUT_FIELD(FShaderParameter,SizeAndPivot);
	LAYOUT_FIELD(FShaderParameter,ZeroPlaneDepth);
};

DECLARE_SHADER_BY_BASE(VS, DrawTextureShader);
DECLARE_SHADER_BY_BASE(PS, DrawTextureShader);
void DrawCopyTexture_GameThread(FVector2D Offset,FTexture* InTexture,FLinearColor InSubtractColor,
	FTextureRenderTargetResource* OutTextureRenderTargetResource,ERHIFeatureLevel::Type FeatureLevel);
void DrawTexture_GameThread(FVector PosAndRotate,FVector4 InSizeAndPivot,FTexture* InDepthTexture,FTexture* InSdfTexture,float zeroPlaneDepth,
	FTextureRenderTargetResource* OutTextureRenderTargetResource,ERHIFeatureLevel::Type FeatureLevel);
void DrawAndCopyTexture_GameThread(FVector2D Offset,FTexture* InCopyTexture,FVector PosAndRotate, FVector4 InSizeAndPivot, FTexture* InDepthTexture,FTexture* InSdfTexture,
	float zeroPlaneDepth,FTextureRenderTargetResource* OutTextureRenderTargetResource, ERHIFeatureLevel::Type FeatureLevel);