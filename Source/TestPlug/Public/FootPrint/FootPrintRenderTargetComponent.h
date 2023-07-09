// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FootPrintRenderTargetComponent.generated.h"


UCLASS(ClassGroup=(FootPrint), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UFootPrintRenderTargetComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFootPrintRenderTargetComponent();
	void ClearRenderTarget(UTextureRenderTarget2D* rt) const;
	void CheckInitialization();
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	void UpdateMaterialParameters(bool OnlySetPosition = true);
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	bool IsInRegion(FVector pos) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void CreateRenderTarget(const TCHAR* Name, UTextureRenderTarget2D*& RenderTarget);
	void CreateMaterialInstance();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	FVector4 CalcCurrentDrawOffset(FVector pos,FVector& newPos) const;
	UFUNCTION(BlueprintCallable, Category="FootPrint")
	void CopyAndMoveRenderTarget(FVector2D Offset) const;
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	void SetLastPosition(FVector Position);
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	FVector GetLastPosition() const;

protected:
	UPROPERTY(EditAnywhere, Category = "FootPrint")
	FVector2D M_RenderTargetSize = FVector2D(1024.f,1024.f);

public:
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	FVector2D RenderTargetSize() const
	{
		return M_RenderTargetSize;
	}
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	EPixelFormat RenderTargetFormat() const
	{
		return M_RenderTargetFormat;
	}
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	UTextureRenderTarget2D* RenderTarget() const
	{
		return M_RenderTarget;
	}
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	UTextureRenderTarget2D* RenderTargetCopy() const
	{
		return M_RenderTargetCopy;
	}
	UFUNCTION(BlueprintCallable, Category = "FootPrint")
	float GetZeroPlaneDepth() const { return FootPrintZeroPlaneDepth;}
protected:
	UPROPERTY(EditAnywhere, Category="FootPrint")
	TEnumAsByte<EPixelFormat> M_RenderTargetFormat = EPixelFormat::PF_G16; 
	UPROPERTY(EditAnywhere,Category= "FootPrint")
	UTextureRenderTarget2D* M_RenderTarget;
	UPROPERTY(VisibleAnywhere,Category= "FootPrint")
	UTextureRenderTarget2D* M_RenderTargetCopy;

	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterial *M_CopyMaterial;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	UMaterialInstanceDynamic *M_CopyMaterialInstance;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	UMaterialParameterCollection *M_MaterialParameterCollection;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	uint32 M_MaterialParameterCollectionIndex = 0;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FBoxSphereBounds M_RegionBounds;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float M_RegionZOffset = 0.0f;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	float FootPrintZeroPlaneDepth = 0.3f;
#if WITH_EDITOR
	UPROPERTY(EditAnywhere,Category="FootPrint")
	bool bDrawRegion = false;
#endif
};
