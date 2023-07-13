// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FootPrintRenderTargetComponent.h"
#include "Components/ActorComponent.h"
#include "FootPrintRender/FootPrintRenderShaderModel.h"
#include "FootPrintComponent.generated.h"

//define ue log FootPrint
DECLARE_LOG_CATEGORY_EXTERN(W_FootPrint,Warning,All);


USTRUCT()
struct FFootPrintTexture
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, Category = "FootPrint")
	UTexture2D *Depth;
	UPROPERTY(EditAnywhere, Category = "FootPrint" )
	UTexture2D *Sdf;
};

UCLASS(ClassGroup=(FootPrint), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UFootPrintComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootPrintComponent();
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	void DrawFootPrint(bool bDrawLast = true,int DrawIndex = 0);
protected:
	void CreateMaterialInstance();
	float CalcFootPrintRotation() const;
	FTexture* GetDrawPrintResource() const;
	void DrawFootPrintReal(bool bDrawLast = true,int DrawIndex = 0) const;
	void DrawFootPrintWithPosition(FVector2D offset,int DrawIndex) const;
	void FindFootPrintTargetComponent();
	void CheckCreateBrush();
	void InitializeFootPrintTexture() const;
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
	TArray<FFootPrintTexture> M_DrawPrintTextures;
	
	// UPROPERTY(VisibleAnywhere,Category= "FootPrint")
	// UTextureRenderTarget2D* M_GenBrush;
	// UPROPERTY(EditAnywhere,Category="FootPrint")
	// UMaterial *M_GenBrushMaterial;
	// UPROPERTY(VisibleAnywhere,Category="FootPrint")
	// UMaterialInstanceDynamic *M_GenBrushMaterialInstance;
	
	
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FVector2D PivotPointOffset = FVector2D(0.f,0.f);
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float RotateOffset = 0.f;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bBeginPlayDraw = true;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bCheckInTargetRegion = false;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	TEnumAsByte<EFootPrintBlendMode> BlendMode = EFootPrintBlendMode::FPBM_Max;
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bAdjustFootPrint = false;
#endif
};
