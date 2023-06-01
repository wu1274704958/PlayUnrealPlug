// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TestMyMesh.generated.h"

UCLASS()
class TESTPLUG_API ATestMyMesh : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestMyMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UMyMeshComponent* MyMeshComponent;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
};
