#include "FootPrintRenderShaderModel.h"

CopyTextureShader::CopyTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
{
	Offset.Bind(Initializer.ParameterMap, TEXT("Offset"));
	Texture.Bind(Initializer.ParameterMap, TEXT("Texture"));
	Sampler.Bind(Initializer.ParameterMap, TEXT("Sampler"));
}

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

DrawTextureShader::DrawTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
	: FGlobalShader(Initializer)
{
	PositionAndRotate.Bind(Initializer.ParameterMap, TEXT("PositionAndRotate"));
	SizeAndPivot.Bind(Initializer.ParameterMap, TEXT("SizeAndPivot"));
	Texture.Bind(Initializer.ParameterMap, TEXT("Texture"));
	Sampler.Bind(Initializer.ParameterMap, TEXT("Sampler"));
	AlphaFactor.Bind(Initializer.ParameterMap, TEXT("AlphaFactor"));
}
bool DrawTextureShader::ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
{
	return IsFeatureLevelSupported(	Parameters.Platform, ERHIFeatureLevel::SM5);
}
void DrawTextureShader::ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters,
	FShaderCompilerEnvironment& OutEnvironment)
{
	FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
}

IMPLEMENT_SHADER_TYPE(,DrawTextureShaderVS,TEXT("/Shaders/DrawTexture.usf"),TEXT("MainVS"),SF_Vertex)
IMPLEMENT_SHADER_TYPE(,DrawTextureShaderPS,TEXT("/Shaders/DrawTexture.usf"),TEXT("MainPS"),SF_Pixel)

void DrawCopyTexture_GameThread(FVector2D Offset,FTexture* InTexture,FTextureRenderTargetResource* OutTextureRenderTargetResource,
                                ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand([Offset,InTexture,OutTextureRenderTargetResource,FeatureLevel](FRHICommandListImmediate& RHICmdList)
	{
		FRHITexture2D *RT = OutTextureRenderTargetResource->GetRenderTargetTexture();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::SRVMask,ERHIAccess::RTV));

		const FRHIRenderPassInfo RenderPassInfo(RT,ERenderTargetActions::DontLoad_Store);
		RHICmdList.BeginRenderPass(RenderPassInfo,TEXT("CopyTexture"));
		{
			const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
			TShaderMapRef<CopyTextureShaderVS> VertexShader(GlobalShaderMap);
			TShaderMapRef<CopyTextureShaderPS> PixelShader(GlobalShaderMap);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.PrimitiveType = PT_TriangleList;
			GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid,CM_None>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false,CF_Always>::GetRHI();
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

			RHICmdList.SetViewport(0,0,0,RT->GetSizeX(),RT->GetSizeY(),1);
			VertexShader->SetParameters(RHICmdList,VertexShader.GetVertexShader(),Offset,InTexture);
			PixelShader->SetParameters(RHICmdList,PixelShader.GetPixelShader(),Offset,InTexture);

			RHICmdList.DrawPrimitive(0,2,0);
		}
		RHICmdList.EndRenderPass();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::RTV,ERHIAccess::SRVMask));
	});
}

void DrawTexture_GameThread(FVector PosAndRotate, FVector4 InSizeAndPivot, FTexture* InTexture,float alphaFactor,
	FTextureRenderTargetResource* OutTextureRenderTargetResource, ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand([PosAndRotate,InSizeAndPivot,InTexture,OutTextureRenderTargetResource,FeatureLevel,alphaFactor](FRHICommandListImmediate& RHICmdList)
	{
		FRHITexture2D* RT = OutTextureRenderTargetResource->GetRenderTargetTexture();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::SRVMask,ERHIAccess::RTV));

		const FRHIRenderPassInfo RenderPassInfo(RT,ERenderTargetActions::Load_Store);
		RHICmdList.BeginRenderPass(RenderPassInfo,TEXT("DrawTexture"));
		{
			const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
			TShaderMapRef<DrawTextureShaderVS> VertexShader(GlobalShaderMap);
			TShaderMapRef<DrawTextureShaderPS> PixelShader(GlobalShaderMap);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.PrimitiveType = PT_TriangleList;
			GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA,BO_Add,BF_SourceAlpha,BF_DestAlpha>::GetRHI();
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid,CM_None>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false,CF_Always>::GetRHI();
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

			RHICmdList.SetViewport(0,0,0,RT->GetSizeX(),RT->GetSizeY(),1);
			FVector RPosAndRotate(
				PosAndRotate.X / static_cast<float>(RT->GetSizeX()),
				PosAndRotate.Y / static_cast<float>(RT->GetSizeY()),
				PosAndRotate.Z);
			FVector4 RSizeAndPivot(
				InSizeAndPivot.X / static_cast<float>(RT->GetSizeX()),
				InSizeAndPivot.Y / static_cast<float>(RT->GetSizeY()),
				InSizeAndPivot.Z,
				InSizeAndPivot.W);
			VertexShader->SetParameters(RHICmdList,VertexShader.GetVertexShader(),RPosAndRotate,RSizeAndPivot,InTexture,alphaFactor);
			PixelShader->SetParameters(RHICmdList,PixelShader.GetPixelShader(),RPosAndRotate,RSizeAndPivot,InTexture,alphaFactor);

			RHICmdList.DrawPrimitive(0,2,0);
		}
		RHICmdList.EndRenderPass();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::RTV,ERHIAccess::SRVMask));
	});
}

void DrawAndCopyTexture_GameThread(FVector2D Offset, FTexture* InCopyTexture, FVector PosAndRotate,
                                   FVector4 InSizeAndPivot, FTexture* InTexture,float alphaFactor,
                                   FTextureRenderTargetResource* OutTextureRenderTargetResource,
                                   ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand(
		[Offset,InCopyTexture,PosAndRotate,InSizeAndPivot,InTexture,OutTextureRenderTargetResource,FeatureLevel,alphaFactor](
		FRHICommandListImmediate& RHICmdList)
		{
			FRHITexture2D* RT = OutTextureRenderTargetResource->GetRenderTargetTexture();
			RHICmdList.Transition(FRHITransitionInfo(RT, ERHIAccess::SRVMask, ERHIAccess::RTV));

			const FRHIRenderPassInfo RenderPassInfo(RT, ERenderTargetActions::DontLoad_Store);

			RHICmdList.BeginRenderPass(RenderPassInfo,TEXT("DrawAndCopyTexture"));
			{
				const FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
				TShaderMapRef<CopyTextureShaderVS> CpVertexShader(GlobalShaderMap);
				TShaderMapRef<CopyTextureShaderPS> CpPixelShader(GlobalShaderMap);
				TShaderMapRef<DrawTextureShaderVS> DrawVertexShader(GlobalShaderMap);
				TShaderMapRef<DrawTextureShaderPS> DrawPixelShader(GlobalShaderMap);

				FGraphicsPipelineStateInitializer GraphicsPSOInit;
				RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
				GraphicsPSOInit.PrimitiveType = PT_TriangleList;
				GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
				GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid, CM_None>::GetRHI();
				GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
				GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
				GraphicsPSOInit.BoundShaderState.VertexShaderRHI = CpVertexShader.GetVertexShader();
				GraphicsPSOInit.BoundShaderState.PixelShaderRHI = CpPixelShader.GetPixelShader();
				SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

				RHICmdList.SetViewport(0, 0, 0, RT->GetSizeX(), RT->GetSizeY(), 1);

				CpVertexShader->SetParameters(RHICmdList, CpVertexShader.GetVertexShader(), Offset, InCopyTexture);
				CpPixelShader->SetParameters(RHICmdList, CpPixelShader.GetPixelShader(), Offset, InCopyTexture);
				//draw copy
				RHICmdList.DrawPrimitive(0, 2, 0);

				GraphicsPSOInit.BoundShaderState.VertexShaderRHI = DrawVertexShader.GetVertexShader();
				GraphicsPSOInit.BoundShaderState.PixelShaderRHI = DrawPixelShader.GetPixelShader();
				GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA,BO_Add,BF_SourceAlpha,BF_DestAlpha>::GetRHI();
				
				SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);
				FVector RPosAndRotate(
					PosAndRotate.X / static_cast<float>(RT->GetSizeX()),
					PosAndRotate.Y / static_cast<float>(RT->GetSizeY()),
					PosAndRotate.Z);
				FVector4 RSizeAndPivot(
					InSizeAndPivot.X / static_cast<float>(RT->GetSizeX()),
					InSizeAndPivot.Y / static_cast<float>(RT->GetSizeY()),
					InSizeAndPivot.Z,
					InSizeAndPivot.W);
				DrawVertexShader->SetParameters(RHICmdList, DrawVertexShader.GetVertexShader(), RPosAndRotate,
				                                RSizeAndPivot, InTexture,alphaFactor);
				DrawPixelShader->SetParameters(RHICmdList, DrawPixelShader.GetPixelShader(), RPosAndRotate,
				                               RSizeAndPivot, InTexture,alphaFactor);

				//draw texture
				RHICmdList.DrawPrimitive(0, 2, 0);
			}
			RHICmdList.EndRenderPass();
			RHICmdList.Transition(FRHITransitionInfo(RT, ERHIAccess::RTV, ERHIAccess::SRVMask));
		});
}
