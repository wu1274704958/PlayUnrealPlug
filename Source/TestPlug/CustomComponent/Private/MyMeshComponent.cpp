// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMeshComponent.h"

#include "DrawDebugHelpers.h"
#include "Chaos/ChaosDebugDraw.h"

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
	PrimaryComponentTick.bCanEverTick = false;
#if WITH_EDITOR
	PrimaryComponentTick.bCanEverTick = true;
#endif
	
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

#if WITH_EDITOR
	if(bShowBounds)
		DrawDebugBox(GetWorld(), Bounds.Origin, Bounds.BoxExtent, FColor::Red, false, 0.f);
#endif
	
}

FBoxSphereBounds UMyMeshComponent::CalcBounds(const FTransform& LocalToWorld) const
{
	FBoxSphereBounds Ret(LocalBounds.TransformBy(LocalToWorld));

	Ret.BoxExtent *= BoundsScale;
	Ret.SphereRadius *= BoundsScale;
	
	return Ret;
}

FPrimitiveSceneProxy* UMyMeshComponent::CreateSceneProxy()
{
	if(!SceneProxy)
		return new FCustomMeshSceneProxy(this);
	return SceneProxy;
}

void UMyMeshComponent::UpdateLocalBounds()
{
	FBox LocalBox(ForceInit);

	for (const FMyMeshSection& Section : Sections)
		LocalBox += Section.Bounds;

	LocalBounds = LocalBox.IsValid ? FBoxSphereBounds(LocalBox) : FBoxSphereBounds(FVector::ZeroVector, FVector::OneVector,0.f);

	UpdateBounds();
	MarkRenderTransformDirty();
}

void UMyMeshComponent::CreateMeshSection(int32 Index, UStaticMesh* StaticMesh)
{
	if(Index >= Sections.Num())
		Sections.SetNum(Index + 1,false);
	auto &Section = Sections[Index];
	Section.Reset();

	Section.StaticMesh = StaticMesh;
	Section.bVisible = true;
	Section.StaticMesh->CalculateExtendedBounds();
	Section.Bounds += Section.StaticMesh->GetBoundingBox();

	SetMaterial(Index, Section.StaticMesh->GetMaterial(0));

	UpdateLocalBounds();
	MarkRenderStateDirty();
	
}

void UMyMeshComponent::ClearMeshSection(int32 Index)
{
	if(Index < Sections.Num())
	{
		Sections[Index].Reset();
		UpdateLocalBounds();
		MarkRenderStateDirty();
	}
}

void UMyMeshComponent::ClearAllMeshSections()
{
	Sections.Empty();
	UpdateLocalBounds();
	MarkRenderStateDirty();
}

int32 UMyMeshComponent::GetNumMeshSections() const
{
	return Sections.Num();
}

void UMyMeshComponent::SetMeshSectionVisibility(int32 Index, bool Visible)
{
	if(Index < Sections.Num())
	{
		Sections[Index].bVisible = Visible;
		if(SceneProxy)
		{
			FCustomMeshSceneProxy* Proxy = static_cast<FCustomMeshSceneProxy*>(SceneProxy);
			ENQUEUE_RENDER_COMMAND(FCustomMeshSceneProxy_SetVisibility)(
				[Proxy, Index, Visible](FRHICommandListImmediate& RHICmdList)
				{
					Proxy->SetSectionVisibility_RenderThread(Index, Visible);		
				}
			);
		}
	}
}

bool UMyMeshComponent::IsMeshSectionVisible(int32 Index) const
{
	return Index < Sections.Num() && Sections[Index].bVisible;
}

int32 UMyMeshComponent::GetNumMaterials() const
{
	return Sections.Num();
}
