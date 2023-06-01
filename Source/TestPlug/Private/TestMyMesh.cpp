// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/TestMyMesh.h"


// Sets default values
ATestMyMesh::ATestMyMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	MyMeshComponent = CreateDefaultSubobject<UMyMeshComponent>(TEXT("MyMeshComponent"));
	
	MyMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATestMyMesh::BeginPlay()
{
	Super::BeginPlay();
	if(StaticMesh)
	{
		MyMeshComponent->CreateMeshSection(0,StaticMesh);
	}
}

// Called every frame
void ATestMyMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

