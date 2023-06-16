// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintRenderTargetComponent.h"

#include "CanvasItem.h"
#include "CanvasTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/TextureRenderTarget2D.h"
#include "FootPrint/FootPrintComponent.h"
#include "FootPrintRender/FootPrintRenderShaderModel.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialParameterCollection.h"


// Sets default values for this component's properties
UFootPrintRenderTargetComponent::UFootPrintRenderTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
#if WITH_EDITOR
	PrimaryComponentTick.bCanEverTick = true;
#endif
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
	M_RegionBounds.BoxExtent.X = M_RenderTargetSize.X;
	M_RegionBounds.BoxExtent.Y = M_RenderTargetSize.Y;
	UpdateMaterialParameters(M_CopyMaterialInstance != nullptr);
	if(M_CopyMaterialInstance == nullptr)
		CreateMaterialInstance();
	if(M_RenderTarget == nullptr)
		CreateRenderTarget(TEXT("FootPrintRenderTarget"),M_RenderTarget);
	else if(M_RenderTarget->SizeX != M_RenderTargetSize.X || M_RenderTarget->SizeY != M_RenderTargetSize.Y)
		M_RenderTarget->ResizeTarget(M_RenderTargetSize.X,M_RenderTargetSize.Y);
	if(M_RenderTargetCopy == nullptr)
		CreateRenderTarget(TEXT("FootPrintRenderTargetCopy"),M_RenderTargetCopy);
	M_RenderTarget->AddressX = M_RenderTarget->AddressY = TextureAddress::TA_Clamp;
	M_RenderTarget->Filter = TextureFilter::TF_Nearest;
	ClearRenderTarget(M_RenderTarget);
}

void UFootPrintRenderTargetComponent::UpdateMaterialParameters(bool OnlySetPosition)
{
	const auto Pos = GetLastPosition();
	if(M_MaterialParameterCollection != nullptr)
	{
		auto& Vectors = M_MaterialParameterCollection->VectorParameters;
		if(Vectors.Num() < static_cast<int32_t>(M_MaterialParameterCollectionIndex) + 2)
			Vectors.AddDefaulted(M_MaterialParameterCollectionIndex + 2);
		if(OnlySetPosition)
			Vectors[M_MaterialParameterCollectionIndex].DefaultValue = FLinearColor(Pos);
		else
		{
			Vectors[M_MaterialParameterCollectionIndex].ParameterName = TEXT("FootPrintTargetPosition");
			Vectors[M_MaterialParameterCollectionIndex + 1].ParameterName = TEXT("FootPrintTargetSize");
			Vectors[M_MaterialParameterCollectionIndex].DefaultValue = FLinearColor(Pos);
			Vectors[M_MaterialParameterCollectionIndex + 1].DefaultValue = FLinearColor(M_RenderTargetSize.X,M_RenderTargetSize.Y,0.0f,0.0f);
		}
		M_MaterialParameterCollection->PreEditChange(nullptr);
		M_MaterialParameterCollection->PostEditChange();
	}
}

bool UFootPrintRenderTargetComponent::IsInRegion(FVector pos) const
{
	return M_RegionBounds.GetBox().IsInside(pos);
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
#if WITH_EDITOR
	if(bDrawRegion)
		DrawDebugBox(GetWorld(), M_RegionBounds.Origin, M_RegionBounds.BoxExtent, FColor::Red, false,0.0f,0,10);
#endif
}

inline float mFloor(float v)
{
	return v >= 0.0f ? floor(v) : ceil(v);	
}

FVector4 UFootPrintRenderTargetComponent::CalcCurrentDrawOffset(FVector pos,FVector& newPos) const
{
	const auto last = GetLastPosition();
	const auto Res = pos - last;
	newPos = last + FVector(mFloor(Res.X),mFloor(Res.Y),Res.Z);
	return FVector4(mFloor(-Res.X) / M_RenderTargetSize.X,mFloor(-Res.Y) / M_RenderTargetSize.Y,Res.Z,0.0f);
}

void UFootPrintRenderTargetComponent::CopyAndMoveRenderTarget(FVector2D Offset) const
{
	check(M_CopyMaterialInstance && M_RenderTarget && M_RenderTargetCopy);
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTarget);
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(Offset.X,Offset.Y,0.0f,0.0f));
	FCanvas Canvas(M_RenderTargetCopy->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem TileItem(FVector2D(0.f,0.f),M_CopyMaterialInstance->GetRenderProxy(), FVector2D(M_RenderTargetSize.X,M_RenderTargetSize.Y));
	Canvas.DrawItem(TileItem);
	Canvas.Flush_GameThread();
}

void UFootPrintRenderTargetComponent::SetLastPosition(FVector Position)
{
	M_RegionBounds.Origin = Position;
	M_RegionBounds.Origin.Z += M_RegionZOffset;
}

FVector UFootPrintRenderTargetComponent::GetLastPosition() const
{
	return FVector(M_RegionBounds.Origin.X,M_RegionBounds.Origin.Y,M_RegionBounds.Origin.Z - M_RegionZOffset);
}

void UFootPrintRenderTargetComponent::CreateRenderTarget(const TCHAR* Name, UTextureRenderTarget2D*& RenderTarget)
{
	RenderTarget = NewObject<UTextureRenderTarget2D>(this,  Name);
	RenderTarget->InitCustomFormat(M_RenderTargetSize.X,M_RenderTargetSize.Y,M_RenderTargetFormat,false);
	RenderTarget->UpdateResourceImmediate();
}
