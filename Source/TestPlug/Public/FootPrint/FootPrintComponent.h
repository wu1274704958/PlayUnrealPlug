// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TextureRenderTarget.h"
#include "FootPrintComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UFootPrintComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootPrintComponent();
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	void DrawFootPrint();
protected:
	void CreateMaterialInstance();
	void CreateRenderTarget(const TCHAR* Name,UTextureRenderTarget2D*& RenderTarget);
	FVector4 CalcCurrentDrawOffset() const;
	void CopyAndMoveRenderTarget(FVector2D Offset) const;
	float CalcFootPrintRotation() const;
	void DrawFootPrintReal() const;
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Category = "FootPrint")
	FVector2D M_RenderTargetSize = FVector2D(1024.f,1024.f);
	UPROPERTY(VisibleAnywhere, Category = "FootPrint")
	FVector M_LastPosition = FVector::ZeroVector;
	UPROPERTY(EditAnywhere,Category= "FootPrint")
	UTextureRenderTarget2D* M_RenderTarget;
	UPROPERTY(VisibleAnywhere,Category= "FootPrint")
	UTextureRenderTarget2D* M_RenderTargetCopy;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector4 M_DrawFootPrintOffsetAndSize;
	// UPROPERTY(EditAnywhere,Category="FootPrint")
	// UMaterial *M_DrawPrintMaterial;
	// UPROPERTY(VisibleAnywhere,Category="FootPrint")
	// UMaterialInstanceDynamic *M_DrawPrintMaterialInstance;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UTexture2D *M_DrawPrintTexture;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterial *M_CopyMaterial;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	UMaterialInstanceDynamic *M_CopyMaterialInstance;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector2D PivotPointOffset = FVector2D(0.f,0.f);
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float RotateOffset = 0.f;
};
