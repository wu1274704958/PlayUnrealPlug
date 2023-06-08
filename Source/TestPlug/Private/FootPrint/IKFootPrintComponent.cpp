// Fill out your copyright notice in the Description page of Project Settings.


#include "FootPrint/IKFootPrintComponent.h"


// Sets default values for this component's properties
UIKFootPrintComponent::UIKFootPrintComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UIKFootPrintComponent::FindFootPrintTransform()
{
	if(SkeletalMeshComponent != nullptr && SkeletalMeshComponent->DoesSocketExist(SocketName))
	{
		SocketTransform = SkeletalMeshComponent->GetSocketTransform(SocketName);
		return true;
	}
#if UE_BUILD_DEBUG || WITH_EDITOR
	UE_LOG(W_FootPrint, Warning, TEXT("FindFootPrintTransform %d %s"), SkeletalMeshComponent == nullptr, *SocketName.ToString());
#endif
	return false;
}

FVector UIKFootPrintComponent::GetFootPrintLocation() const
{
	return SocketTransform.GetLocation();
}

FRotator UIKFootPrintComponent::GetFootPrintRotation() const
{
	return SocketTransform.GetRotation().Rotator();
}

FVector UIKFootPrintComponent::GetFootPrintScale() const
{
	return SocketTransform.GetScale3D();
}

void UIKFootPrintComponent::OnDrawFootPrint()
{
	FindFootPrintTransform();
}

void UIKFootPrintComponent::FindSkeletalMeshComponent()
{
	if(SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	}
}


// Called when the game starts
void UIKFootPrintComponent::BeginPlay()
{
	FindSkeletalMeshComponent();
	FindFootPrintTransform();
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UIKFootPrintComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

