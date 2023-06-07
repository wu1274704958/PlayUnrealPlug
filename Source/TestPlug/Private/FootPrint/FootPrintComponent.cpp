// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintComponent.h"


#include "CanvasItem.h"
#include "RendererInterface.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"


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
	if(M_CopyMaterial != nullptr)
		M_CopyMaterialInstance = UMaterialInstanceDynamic::Create(M_CopyMaterial, this);
}

float UFootPrintComponent::CalcFootPrintRotation() const
{
	return GetComponentRotation().Yaw;
}

void UFootPrintComponent::DrawFootPrintReal() const
{
	const auto RenderTargetSize = M_RenderTargetComponent->RenderTargetSize();
	M_CopyMaterialInstance->SetTextureParameterValue(TEXT("RenderTarget"), M_RenderTargetComponent->RenderTargetCopy());
	M_CopyMaterialInstance->SetVectorParameterValue(TEXT("Offset"), FLinearColor(0,0,0.0f,0.0f));
	const FVector2D PrintSize = FVector2D(M_DrawFootPrintOffsetAndSize.Z,M_DrawFootPrintOffsetAndSize.W);
	FCanvas Canvas(M_RenderTargetComponent->RenderTarget()->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
	Canvas.Clear(FLinearColor::Transparent);
	FCanvasTileItem LastItem(FVector2D(),M_CopyMaterialInstance->GetRenderProxy(), RenderTargetSize);
	FCanvasTileItem TileItem(RenderTargetSize * 0.5f - PrintSize * 0.5f
		 + FVector2D(M_DrawFootPrintOffsetAndSize.X,M_DrawFootPrintOffsetAndSize.Y),
		M_DrawPrintTexture->GetResource(),PrintSize,FLinearColor::White);
	TileItem.Rotation = FRotator(0,CalcFootPrintRotation() + RotateOffset,0.0f);
	TileItem.PivotPoint = FVector2D(0.5f,0.5f) + PivotPointOffset;
	Canvas.DrawItem(LastItem);
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

void UFootPrintComponent::DrawFootPrint()
{
	check(M_RenderTargetComponent && M_DrawPrintTexture);
	
	const auto Offset = FVector2D(M_RenderTargetComponent->CalcCurrentDrawOffset(GetComponentLocation()));
	M_RenderTargetComponent->SetLastPosition(this->GetComponentLocation());
	M_RenderTargetComponent->CopyAndMoveRenderTarget(Offset);
	DrawFootPrintReal();
	M_RenderTargetComponent->UpdateMaterialParameters();
}


// Called when the game starts
void UFootPrintComponent::BeginPlay()
{
	Super::BeginPlay();
	if(M_RenderTargetComponent == nullptr)
		FindFootPrintTargetComponent();
	M_RenderTargetComponent->CheckInitialization();
	M_RenderTargetComponent->SetLastPosition(this->GetComponentLocation());
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

