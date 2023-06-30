// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/FootPrint/FootPrintComponent.h"


#include "CanvasItem.h"
#include "Engine/TextureRenderTarget2D.h"
#include "FootPrintRender/FootPrintRenderShaderModel.h"
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
	if(M_GenBrushMaterial != nullptr)
		M_GenBrushMaterialInstance = UMaterialInstanceDynamic::Create(M_GenBrushMaterial, this);
}

float UFootPrintComponent::CalcFootPrintRotation() const
{
	return GetFootPrintRotation().Yaw;
}

FTexture* UFootPrintComponent::GetDrawPrintResource() const
{
	return M_GenBrush != nullptr ? M_GenBrush->GetResource() : M_DrawPrintTexture->GetResource();
}

void UFootPrintComponent::DrawFootPrintReal(bool bDrawLast) const
{
	const auto RenderTargetSize = M_RenderTargetComponent->RenderTargetSize();
	const auto FootPrintScale = FVector2D(GetFootPrintScale());
	const FVector2D PrintSize = FVector2D(M_DrawFootPrintOffsetAndSize.Z,M_DrawFootPrintOffsetAndSize.W);
	DrawAndCopyTexture_GameThread(FVector2D(0.f,0.f),M_RenderTargetComponent->RenderTargetCopy()->GetResource(),
		FVector(RenderTargetSize * 0.5f + FVector2D(M_DrawFootPrintOffsetAndSize.X,M_DrawFootPrintOffsetAndSize.Y),CalcFootPrintRotation() + RotateOffset),
		FVector4(PrintSize * FootPrintScale,PivotPointOffset),
		GetDrawPrintResource(),FootPrintAlphaFactor,M_RenderTargetComponent->RenderTarget()->GameThread_GetRenderTargetResource(),GMaxRHIFeatureLevel);
}

void UFootPrintComponent::DrawFootPrintWithPosition(FVector2D pos) const
{
	const FVector2D PrintSize = FVector2D(M_DrawFootPrintOffsetAndSize.Z,M_DrawFootPrintOffsetAndSize.W);
	const auto RenderTargetSize = M_RenderTargetComponent->RenderTargetSize();
	const auto FootPrintScale = FVector2D(GetFootPrintScale());

	const auto Pos = RenderTargetSize * 0.5f + FVector2D(M_DrawFootPrintOffsetAndSize.X,M_DrawFootPrintOffsetAndSize.Y) + pos;
	DrawTexture_GameThread(FVector(Pos,CalcFootPrintRotation() + RotateOffset),FVector4(PrintSize * FootPrintScale,PivotPointOffset),
		GetDrawPrintResource(),FootPrintAlphaFactor,M_RenderTargetComponent->RenderTarget()->GameThread_GetRenderTargetResource(),GMaxRHIFeatureLevel);
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


void UFootPrintComponent::CheckCreateBrush()
{
	if(M_GenBrushMaterialInstance != nullptr)
	{
		M_GenBrush = NewObject<UTextureRenderTarget2D>(this,  "FootPrintGenBrush");
		M_GenBrush->InitCustomFormat(M_DrawPrintTexture->GetSizeX(),M_DrawPrintTexture->GetSizeY(),PF_R8G8B8A8,false);
		M_GenBrush->UpdateResourceImmediate();

		M_GenBrushMaterialInstance->SetTextureParameterValue(TEXT("Texture"),M_DrawPrintTexture);
		FCanvas Canvas(M_GenBrush->GameThread_GetRenderTargetResource(), nullptr,GetWorld(), GMaxRHIFeatureLevel);
		Canvas.Clear(FLinearColor::Black);
		FCanvasTileItem Item(FVector2D(0.0f,0.0f),M_GenBrushMaterialInstance->GetRenderProxy(), FVector2D(M_DrawPrintTexture->GetSizeX(),M_DrawPrintTexture->GetSizeY()));
		Canvas.DrawItem(Item);
		Canvas.Flush_GameThread();
	}
}

void UFootPrintComponent::DrawFootPrint(bool bDrawLast)
{
	if(M_RenderTargetComponent && M_DrawPrintTexture )
	{
		OnDrawFootPrint();
		const FVector printLocation = GetFootPrintLocation();
		if(bCheckInTargetRegion)
		{
			if( M_RenderTargetComponent->IsInRegion(printLocation))
			{
				const auto pos = FVector2D(printLocation - M_RenderTargetComponent->GetLastPosition());
				DrawFootPrintWithPosition(-pos);
				//UE_LOG(W_FootPrint, Warning, TEXT("%s InRegion draw foot print pos: %s"), *GetName(),*pos.ToString());
			}
		}else{
			FVector newPosition; 
			const auto Offset = FVector2D(M_RenderTargetComponent->CalcCurrentDrawOffset(printLocation,newPosition));
			//UE_LOG(W_FootPrint, Warning, TEXT("%s draw foot print Offset: %s"), *GetName(),*Offset.ToString());
			M_RenderTargetComponent->SetLastPosition(newPosition);
			M_RenderTargetComponent->CopyAndMoveRenderTarget(Offset);
			DrawFootPrintReal(bDrawLast);
			M_RenderTargetComponent->UpdateMaterialParameters();
		}
	}
}


// Called when the game starts
void UFootPrintComponent::BeginPlay()
{
	Super::BeginPlay();
	if(M_RenderTargetComponent == nullptr)
		FindFootPrintTargetComponent();
	if(M_RenderTargetComponent == nullptr) return;
	M_RenderTargetComponent->CheckInitialization();
	M_RenderTargetComponent->SetLastPosition(this->GetFootPrintLocation());
	CreateMaterialInstance();
	CheckCreateBrush();
	if(bBeginPlayDraw)DrawFootPrint();
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

