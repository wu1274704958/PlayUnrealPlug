#include "FootPrintRenderShaderModel.h"

bool CopyTextureShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
	return IsFeatureLevelSupported(	Parameters.Platform, ERHIFeatureLevel::SM5);
}

void CopyTextureShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
}


IMPLEMENT_SHADER_TYPE(,CopyTextureShaderVS,TEXT("/Shaders/CopyTexture.usf"),TEXT("MainVS"),SF_Vertex)
IMPLEMENT_SHADER_TYPE(,CopyTextureShaderPS,TEXT("/Shaders/CopyTexture.usf"),TEXT("MainPS"),SF_Pixel)

void DrawCopyTexture_GameThread(FVector2D Offset,const FTexture* InTexture,FTextureRenderTargetResource* OutTextureRenderTargetResource)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand([Offset,InTexture,OutTextureRenderTargetResource](FRHICommandListImmediate& RHICmdList)
	{
		FRHITexture2D *RT = OutTextureRenderTargetResource->GetRenderTargetTexture();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::SRVMask,ERHIAccess::RTV));

		FRHIRenderPassInfo RenderPassInfo(RT,ERenderTargetActions::DontLoad_Store);
		RHICmdList.BeginRenderPass(RenderPassInfo,TEXT("CopyTexture"));
		
	});
}