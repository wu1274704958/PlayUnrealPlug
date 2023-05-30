// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMeshComponent.h"

FMyMeshSection::FMyMeshSection() : StaticMesh(nullptr), Bounds(FBox(FVector::ZeroVector, FVector::OneVector)), bVisible(false)
{
}

FMyMeshSection::FMyMeshSection(UStaticMesh* StaticMesh, const FBox& Bounds, bool bVisible)
		: StaticMesh(StaticMesh),
		  Bounds(Bounds),
		  bVisible(bVisible)
{
}

void FMyMeshSection::Reset()
{
	StaticMesh = nullptr;
	Bounds = FBox(FVector::ZeroVector, FVector::OneVector);
	bVisible = false;
}


// Sets default values for this component's properties
UMyMeshComponent::UMyMeshComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UMyMeshComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
