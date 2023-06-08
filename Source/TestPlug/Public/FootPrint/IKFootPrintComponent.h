// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FootPrint/FootPrintComponent.h"
#include "IKFootPrintComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UIKFootPrintComponent : public UFootPrintComponent
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UIKFootPrintComponent();

protected:
	bool FindFootPrintTransform();
	virtual FVector GetFootPrintLocation() const override;
	virtual FRotator GetFootPrintRotation() const override;
	virtual FVector GetFootPrintScale() const override;
	virtual void OnDrawFootPrint() override;
	void FindSkeletalMeshComponent();
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere,Category="FootPrint")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditAnywhere,Category="FootPrint")
	FName SocketName;
	UPROPERTY(VisibleAnywhere,Category="FootPrint")
	FTransform SocketTransform;
};
