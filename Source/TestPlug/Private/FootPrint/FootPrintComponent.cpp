﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintComponent.h"

#include <valarray>

#include "CanvasItem.h"
#include "RendererInterface.h"
#include "Engine/TextureRenderTarget2D.h"


// Sets default values for this component's properties
UFootPrintComponent::UFootPrintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UFootPrintComponent::CreateMaterialInstance()
{
	// if(M_DrawPrintMaterial != nullptr)
	// 	M_DrawPrintMaterialInstance = UMaterialInstanceDynamic::Create(M_DrawPrintMaterial, this);
	if(M_CopyMaterial != nullptr)
		M_CopyMaterialInstance = UMaterialInstanceDynamic::Create(M_CopyMaterial, this);
}

void UFootPrintComponent::CreateRenderTarget(const TCHAR* Name, UTextureRenderTarget2D*& RenderTarget)
{
	RenderTarget = NewObject<UTextureRenderTarget2D>(this,  Name);
	RenderTarget->InitCustomFormat(M_RenderTargetSize.X,M_RenderTargetSize.Y,EPixelFormat::PF_R8G8B8A8,false);
	RenderTarget->UpdateResourceImmediate();
}

FVector4 UFootPrintComponent::CalcCurrentDrawOffset() const
{
	const auto Res = GetComponentLocation() - M_LastPosition;
	return FVector4(Res.X / M_RenderTargetSize.X,Res.Y / M_RenderTargetSize.Y,Res.Z,0.0f);
}

void UFootPrintComponent::CopyAndMoveRenderTarget(FVector2D Offset) const
{
	check(M_CopyMaterialInstance);
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTarget);
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(Offset.X,Offset.Y,0.0f,0.0f));
	FCanvas Canvas(M_RenderTargetCopy->GameThread_GetRenderTargetResource(), NULL,FApp::GetCurrentTime() - GStartTime,
		FApp::GetDeltaTime(), FApp::GetCurrentTime() - GStartTime, GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem TileItem(FVector2D(),M_CopyMaterialInstance->GetRenderProxy(), FVector2D(M_RenderTargetSize.X,M_RenderTargetSize.Y));
	Canvas.DrawItem(TileItem);
	Canvas.Flush_GameThread();
}

float UFootPrintComponent::CalcFootPrintRotation() const
{
	return GetComponentRotation().Yaw;
}

void UFootPrintComponent::DrawFootPrintReal() const
{
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTargetCopy);
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(0,0,0.0f,0.0f));
	const FVector2D PrintSize = FVector2D(M_DrawFootPrintOffsetAndSize.Z,M_DrawFootPrintOffsetAndSize.W);
	FCanvas Canvas(M_RenderTarget->GameThread_GetRenderTargetResource(), NULL,FApp::GetCurrentTime() - GStartTime,
		FApp::GetDeltaTime(), FApp::GetCurrentTime() - GStartTime, GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem LastItem(FVector2D(),M_CopyMaterialInstance->GetRenderProxy(), FVector2D(M_RenderTargetSize.X,M_RenderTargetSize.Y));
	FCanvasTileItem TileItem(FVector2D(M_RenderTargetSize.X,M_RenderTargetSize.Y) * 0.5f - PrintSize * 0.5f
		 + FVector2D(M_DrawFootPrintOffsetAndSize.X,M_DrawFootPrintOffsetAndSize.Y),
		M_DrawPrintTexture->GetResource(),PrintSize,FLinearColor::White);
	TileItem.Rotation = FRotator(0,CalcFootPrintRotation() + RotateOffset,0.0f);
	TileItem.PivotPoint = FVector2D(0.5f,0.5f) + PivotPointOffset;
	Canvas.DrawItem(LastItem);
	Canvas.DrawItem(TileItem);
	Canvas.Flush_GameThread();
}

void UFootPrintComponent::DrawFootPrint()
{
	check(M_RenderTarget && M_DrawPrintTexture);
	
	const auto Offset = FVector2D(CalcCurrentDrawOffset());
	M_LastPosition = this->GetComponentLocation();
	CopyAndMoveRenderTarget(Offset);
	DrawFootPrintReal();
}


// Called when the game starts
void UFootPrintComponent::BeginPlay()
{
	Super::BeginPlay();
	M_LastPosition = this->GetComponentLocation();
	if(M_RenderTarget == nullptr)
		CreateRenderTarget(TEXT("FootPrintRenderTarget"),M_RenderTarget);
	CreateRenderTarget(TEXT("FootPrintRenderTargetCopy"),M_RenderTargetCopy);
	CreateMaterialInstance();
	DrawFootPrint();
	// ...
}


// Called every frame
void UFootPrintComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

