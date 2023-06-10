// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FootPrintRenderTargetComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/TextureRenderTarget.h"
#include "FootPrintComponent.generated.h"

//define ue log FootPrint
DECLARE_LOG_CATEGORY_EXTERN(W_FootPrint,Warning,All);


UCLASS(ClassGroup=(FootPrint), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UFootPrintComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootPrintComponent();
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	void DrawFootPrint(bool bDrawLast = true);
protected:
	void CreateMaterialInstance();
	float CalcFootPrintRotation() const;
	void DrawFootPrintReal(bool bDrawLast = true) const;
	void FindFootPrintTargetComponent();
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual FVector GetFootPrintLocation() const;
	virtual FRotator GetFootPrintRotation() const;
	virtual FVector GetFootPrintScale() const;
	virtual void OnDrawFootPrint();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector4 M_DrawFootPrintOffsetAndSize;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UFootPrintRenderTargetComponent* M_RenderTargetComponent;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UTexture2D *M_DrawPrintTexture;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterial *M_CopyMaterial;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	UMaterialInstanceDynamic *M_CopyMaterialInstance;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterial *M_DrawMaterial;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	UMaterialInstanceDynamic *M_DrawMaterialInstance;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector2D PivotPointOffset = FVector2D(0.f,0.f);
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float RotateOffset = 0.f;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool BeginPlayDraw = true;
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bAdjustFootPrint = false;
#endif
};
