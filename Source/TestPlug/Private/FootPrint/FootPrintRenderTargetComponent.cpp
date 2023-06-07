// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintRenderTargetComponent.h"

#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"


// Sets default values for this component's properties
UFootPrintRenderTargetComponent::UFootPrintRenderTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UFootPrintRenderTargetComponent::ClearRenderTarget(UTextureRenderTarget2D* rt) const
{
	if(rt != nullptr)
	{
		FCanvas Canvas(rt->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
		Canvas.Clear(FLinearColor::Transparent);
		Canvas.Flush_GameThread();
	}
}

void UFootPrintRenderTargetComponent::CheckInitialization()
{
	UpdateMaterialParameters(M_CopyMaterialInstance != nullptr);
	if(M_CopyMaterialInstance == nullptr)
		CreateMaterialInstance();
	if(M_RenderTarget == nullptr)
		CreateRenderTarget(TEXT("FootPrintRenderTarget"),M_RenderTarget);
	else if(M_RenderTarget->SizeX != M_RenderTargetSize.X || M_RenderTarget->SizeY != M_RenderTargetSize.Y)
		M_RenderTarget->ResizeTarget(M_RenderTargetSize.X,M_RenderTargetSize.Y);
	if(M_RenderTargetCopy == nullptr)
		CreateRenderTarget(TEXT("FootPrintRenderTargetCopy"),M_RenderTargetCopy);
	if(M_RenderTarget)
	ClearRenderTarget(M_RenderTarget);
}

void UFootPrintRenderTargetComponent::UpdateMaterialParameters(bool OnlySetPosition) const
{
	if(M_MaterialParameterCollection != nullptr)
	{
		auto& Vectors = M_MaterialParameterCollection->VectorParameters;
		if(Vectors.Num() < static_cast<int32_t>(M_MaterialParameterCollectionIndex) + 2)
			Vectors.AddDefaulted(M_MaterialParameterCollectionIndex + 2);
		if(OnlySetPosition)
			Vectors[M_MaterialParameterCollectionIndex].DefaultValue = FLinearColor(GetLastPosition());
		else
		{
			Vectors[M_MaterialParameterCollectionIndex].ParameterName = TEXT("FootPrintTargetPosition");
			Vectors[M_MaterialParameterCollectionIndex + 1].ParameterName = TEXT("FootPrintTargetSize");
			Vectors[M_MaterialParameterCollectionIndex].DefaultValue = FLinearColor(GetLastPosition());
			Vectors[M_MaterialParameterCollectionIndex + 1].DefaultValue = FLinearColor(M_RenderTargetSize.X,M_RenderTargetSize.Y,0.0f,0.0f);
		}
		M_MaterialParameterCollection->PreEditChange(nullptr);
		M_MaterialParameterCollection->PostEditChange();
	}
}

void UFootPrintRenderTargetComponent::CreateMaterialInstance()
{
	if(M_CopyMaterial != nullptr)
		M_CopyMaterialInstance = UMaterialInstanceDynamic::Create(M_CopyMaterial, this);
}
// Called when the game starts
void UFootPrintRenderTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	CheckInitialization();
}


// Called every frame
void UFootPrintRenderTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector4 UFootPrintRenderTargetComponent::CalcCurrentDrawOffset(FVector pos) const
{
	const auto Res = GetLastPosition() - pos;
	return FVector4(floor(Res.X) / M_RenderTargetSize.X,floor(Res.Y) / M_RenderTargetSize.Y,Res.Z,0.0f);
}

void UFootPrintRenderTargetComponent::CopyAndMoveRenderTarget(FVector2D Offset) const
{
	check(M_CopyMaterialInstance && M_RenderTarget && M_RenderTargetCopy);
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTarget);
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(Offset.X,Offset.Y,0.0f,0.0f));
	FCanvas Canvas(M_RenderTargetCopy->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem TileItem(FVector2D(),M_CopyMaterialInstance->GetRenderProxy(), FVector2D(M_RenderTargetSize.X,M_RenderTargetSize.Y));
	Canvas.DrawItem(TileItem);
	Canvas.Flush_GameThread();
}

void UFootPrintRenderTargetComponent::SetLastPosition(FVector Position)
{
	GetOwner()->SetActorLocation(Position);
}

FVector UFootPrintRenderTargetComponent::GetLastPosition() const
{
	return GetOwner()->GetActorLocation();
}

void UFootPrintRenderTargetComponent::CreateRenderTarget(const TCHAR* Name, UTextureRenderTarget2D*& RenderTarget)
{
	RenderTarget = NewObject<UTextureRenderTarget2D>(this,  Name);
	RenderTarget->InitCustomFormat(M_RenderTargetSize.X,M_RenderTargetSize.Y,M_RenderTargetFormat,false);
	RenderTarget->UpdateResourceImmediate();
}
