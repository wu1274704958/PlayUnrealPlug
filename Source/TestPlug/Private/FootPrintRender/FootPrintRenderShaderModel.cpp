#include "FootPrintRenderShaderModel.h"

CopyTextureShader::CopyTextureShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
{
	Offset.Bind(Initializer.ParameterMap, TEXT("Offset"));
	Texture.Bind(Initializer.ParameterMap, TEXT("Texture"));
	Sampler.Bind(Initializer.ParameterMap, TEXT("Sampler"));
	SubtractColor.Bind(Initializer.ParameterMap, TEXT("SubtractColor"));
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
	DepthTexture.Bind(Initializer.ParameterMap, TEXT("DepthTexture"));
	DepthSampler.Bind(Initializer.ParameterMap, TEXT("DepthSampler"));
	SdfTexture.Bind(Initializer.ParameterMap, TEXT("SdfTexture"));
	SdfSampler.Bind(Initializer.ParameterMap, TEXT("SdfSampler"));
	NoiseAndZeroPlaneDepth.Bind(Initializer.ParameterMap, TEXT("NoiseAndZeroPlaneDepth"));
	EdgeValue.Bind(Initializer.ParameterMap, TEXT("EdgeValue"));
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

void DrawCopyTexture_GameThread(FVector2D Offset,FTexture* InTexture,FLinearColor InSubtractColor,FTextureRenderTargetResource* OutTextureRenderTargetResource,
                                ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand([Offset,InTexture,OutTextureRenderTargetResource,FeatureLevel,InSubtractColor](FRHICommandListImmediate& RHICmdList)
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
			VertexShader->SetParameters(RHICmdList,VertexShader.GetVertexShader(),Offset,InTexture,InSubtractColor);
			PixelShader->SetParameters(RHICmdList,PixelShader.GetPixelShader(),Offset,InTexture,InSubtractColor);

			RHICmdList.DrawPrimitive(0,2,0);
		}
		RHICmdList.EndRenderPass();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::RTV,ERHIAccess::SRVMask));
	});
}

FORCEINLINE void SetBlendMode_RenderThread(FGraphicsPipelineStateInitializer& GraphicsPSOInit,EFootPrintBlendMode BlendMode)
{
	switch (BlendMode)
	{
	case FPBM_Add: GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA,BO_Add,BF_One,BF_One,BO_Add,BF_One,BF_One>::GetRHI(); break;
	case FPBM_Max: GraphicsPSOInit.BlendState = TStaticBlendState<CW_RGBA,BO_Max,BF_One,BF_One,BO_Max,BF_One,BF_One>::GetRHI(); break;
	default: GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();break;
	}
}

void DrawTexture_GameThread(const FDrawFootPrintModel& DrawFootPrintModel,FTextureRenderTargetResource* OutTextureRenderTargetResource, ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand([DrawFootPrintModel,OutTextureRenderTargetResource,FeatureLevel](FRHICommandListImmediate& RHICmdList)
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
			SetBlendMode_RenderThread(GraphicsPSOInit,DrawFootPrintModel.BlendMode);
			GraphicsPSOInit.RasterizerState = TStaticRasterizerState<FM_Solid,CM_None>::GetRHI();
			GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false,CF_Always>::GetRHI();
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GetVertexDeclarationFVector4();
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
			SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);

			RHICmdList.SetViewport(0,0,0,RT->GetSizeX(),RT->GetSizeY(),1);
			FVector RPosAndRotate(
				DrawFootPrintModel.PosAndRotate.X / static_cast<float>(RT->GetSizeX()),
				DrawFootPrintModel.PosAndRotate.Y / static_cast<float>(RT->GetSizeY()),
				DrawFootPrintModel.PosAndRotate.Z);
			FVector4 RSizeAndPivot(
				DrawFootPrintModel.SizeAndPivot.X / static_cast<float>(RT->GetSizeX()),
				DrawFootPrintModel.SizeAndPivot.Y / static_cast<float>(RT->GetSizeY()),
				DrawFootPrintModel.SizeAndPivot.Z,
				DrawFootPrintModel.SizeAndPivot.W);
			VertexShader->SetParameters(RHICmdList,VertexShader.GetVertexShader(),RPosAndRotate,RSizeAndPivot,
				DrawFootPrintModel.DepthTexture,DrawFootPrintModel.SdfTexture,DrawFootPrintModel.NoiseAndZeroPlaneDepth,
				DrawFootPrintModel.EdgeValue1);
			PixelShader->SetParameters(RHICmdList,PixelShader.GetPixelShader(),RPosAndRotate,RSizeAndPivot,
				DrawFootPrintModel.DepthTexture,DrawFootPrintModel.SdfTexture,DrawFootPrintModel.NoiseAndZeroPlaneDepth,
				DrawFootPrintModel.EdgeValue1);

			RHICmdList.DrawPrimitive(0,2,0);
		}
		RHICmdList.EndRenderPass();
		RHICmdList.Transition(FRHITransitionInfo(RT,ERHIAccess::RTV,ERHIAccess::SRVMask));
	});
}

void DrawAndCopyTexture_GameThread(FVector2D Offset, FTexture* InCopyTexture,const FDrawFootPrintModel& Model,
                                   FTextureRenderTargetResource* OutTextureRenderTargetResource,
                                   ERHIFeatureLevel::Type FeatureLevel)
{
	FRenderThreadScope RenderScope;
	RenderScope.EnqueueRenderCommand(
		[Offset,InCopyTexture,Model,OutTextureRenderTargetResource,FeatureLevel](
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
				SetBlendMode_RenderThread(GraphicsPSOInit, Model.BlendMode);
				
				SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit);
				FVector RPosAndRotate(
					Model.PosAndRotate.X / static_cast<float>(RT->GetSizeX()),
					Model.PosAndRotate.Y / static_cast<float>(RT->GetSizeY()),
					Model.PosAndRotate.Z);
				FVector4 RSizeAndPivot(
					Model.SizeAndPivot.X / static_cast<float>(RT->GetSizeX()),
					Model.SizeAndPivot.Y / static_cast<float>(RT->GetSizeY()),
					Model.SizeAndPivot.Z,
					Model.SizeAndPivot.W);
				DrawVertexShader->SetParameters(RHICmdList, DrawVertexShader.GetVertexShader(), RPosAndRotate,
				                                RSizeAndPivot, Model.DepthTexture,Model.SdfTexture,Model.NoiseAndZeroPlaneDepth,Model.EdgeValue1);
				DrawPixelShader->SetParameters(RHICmdList, DrawPixelShader.GetPixelShader(), RPosAndRotate,
				                               RSizeAndPivot, Model.DepthTexture,Model.SdfTexture,Model.NoiseAndZeroPlaneDepth,Model.EdgeValue1);

				//draw texture
				RHICmdList.DrawPrimitive(0, 2, 0);
			}
			RHICmdList.EndRenderPass();
			RHICmdList.Transition(FRHITransitionInfo(RT, ERHIAccess::RTV, ERHIAccess::SRVMask));
		});
}
