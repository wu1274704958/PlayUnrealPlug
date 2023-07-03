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
	FTexture* GetDrawPrintResource() const;
	void DrawFootPrintReal(bool bDrawLast = true) const;
	void DrawFootPrintWithPosition(FVector2D offset) const;
	void FindFootPrintTargetComponent();
	void CheckCreateBrush();
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
	
	UPROPERTY(VisibleAnywhere,Category= "FootPrint")
	UTextureRenderTarget2D* M_GenBrush;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterial *M_GenBrushMaterial;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	UMaterialInstanceDynamic *M_GenBrushMaterialInstance;
	
	
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector2D PivotPointOffset = FVector2D(0.f,0.f);
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float RotateOffset = 0.f;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bBeginPlayDraw = true;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bCheckInTargetRegion = false;
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bAdjustFootPrint = false;
#endif
};
