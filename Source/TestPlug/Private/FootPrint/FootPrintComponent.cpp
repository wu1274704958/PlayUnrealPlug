// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintComponent.h"


#include "CanvasItem.h"
#include "RendererInterface.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(W_FootPrint);

// Sets default values for this component's properties
UFootPrintComponent::UFootPrintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
#if WITH_EDITOR
	PrimaryComponentTick.bCanEverTick = true;
#endif
	// ...
}

void UFootPrintComponent::CreateMaterialInstance()
{
	if(M_CopyMaterial != nullptr)
		M_CopyMaterialInstance = UMaterialInstanceDynamic::Create(M_CopyMaterial, this);
	if(M_DrawMaterial != nullptr)
		M_DrawMaterialInstance = UMaterialInstanceDynamic::Create(M_DrawMaterial,this);
}

float UFootPrintComponent::CalcFootPrintRotation() const
{
	return GetFootPrintRotation().Yaw;
}

void UFootPrintComponent::DrawFootPrintReal(bool bDrawLast) const
{
	const auto RenderTargetSize = M_RenderTargetComponent->RenderTargetSize();
	const auto FootPrintScale = FVector2D(GetFootPrintScale());
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTargetComponent->RenderTargetCopy());
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(0,0,0.0f,0.0f));
	M_DrawMaterialInstance->SetTextureParameterValue(TEXT("Texture"),M_DrawPrintTexture);
	const FVector2D PrintSize = FVector2D(M_DrawFootPrintOffsetAndSize.Z,M_DrawFootPrintOffsetAndSize.W);
	FCanvas Canvas(M_RenderTargetComponent->RenderTarget()->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem LastItem(FVector2D(),M_CopyMaterialInstance->GetRenderProxy(), RenderTargetSize);
	FCanvasTileItem TileItem(RenderTargetSize * 0.5f - PrintSize * 0.5f
		 + FVector2D(M_DrawFootPrintOffsetAndSize.X,M_DrawFootPrintOffsetAndSize.Y),
		M_DrawMaterialInstance->GetRenderProxy(),PrintSize * FootPrintScale);
	TileItem.Rotation = FRotator(0,CalcFootPrintRotation() + RotateOffset,0.0f);
	TileItem.PivotPoint = FVector2D(0.5f,0.5f) + PivotPointOffset;
	if(bDrawLast)Canvas.DrawItem(LastItem);
	Canvas.DrawItem(TileItem);
	Canvas.Flush_GameThread();
}

void UFootPrintComponent::FindFootPrintTargetComponent()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("FootPrintTarget"), Actors);
	for(int i = 0;i < Actors.Num();i++)
	{
		const auto comp = Actors[i]->GetComponentByClass(UFootPrintRenderTargetComponent::StaticClass());
		if(comp != nullptr)
		{
			M_RenderTargetComponent = Cast<UFootPrintRenderTargetComponent>(comp);
			return;
		}
	}
}

void UFootPrintComponent::DrawFootPrint(bool bDrawLast)
{
	if(M_RenderTargetComponent && M_DrawPrintTexture && M_DrawMaterialInstance)
	{
		OnDrawFootPrint();
		FVector newPosition; 
		const auto Offset = FVector2D(M_RenderTargetComponent->CalcCurrentDrawOffset(GetFootPrintLocation(),newPosition));
		//UE_LOG(W_FootPrint, Warning, TEXT("Offset: %s"), *Offset.ToString());
		M_RenderTargetComponent->SetLastPosition(newPosition);
		M_RenderTargetComponent->CopyAndMoveRenderTarget(Offset);
		DrawFootPrintReal(bDrawLast);
		M_RenderTargetComponent->UpdateMaterialParameters();
	}
}


// Called when the game starts
void UFootPrintComponent::BeginPlay()
{
	Super::BeginPlay();
	if(M_RenderTargetComponent == nullptr)
		FindFootPrintTargetComponent();
	M_RenderTargetComponent->CheckInitialization();
	M_RenderTargetComponent->SetLastPosition(this->GetFootPrintLocation());
	CreateMaterialInstance();
	if(BeginPlayDraw)DrawFootPrint();
	// ...
}

FVector UFootPrintComponent::GetFootPrintLocation() const
{
	return GetComponentLocation();
}

FRotator UFootPrintComponent::GetFootPrintRotation() const
{
	return GetComponentRotation();
}

FVector UFootPrintComponent::GetFootPrintScale() const
{
	return FVector::OneVector;
}

void UFootPrintComponent::OnDrawFootPrint()
{
}


// Called every frame
void UFootPrintComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
#if WITH_EDITOR
	if(bAdjustFootPrint)
	{
		// const auto PlayerController = GetWorld()->GetFirstPlayerController();
		// if (PlayerController && PlayerController->IsInputKeyDown(EKeys::T))
		{
			DrawFootPrint(false);
		}
	}
	
#endif
	
}

