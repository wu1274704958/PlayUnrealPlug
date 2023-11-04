// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "MyMeshComponent.generated.h"


USTRUCT()
struct TESTPLUG_API FMyMeshSection
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere)
	FTransform SectionTransform;
	UPROPERTY()
	FBox Bounds;
	UPROPERTY(EditAnywhere)
	bool bVisible;

	FMyMeshSection();
	FMyMeshSection(UStaticMesh* StaticMesh, const FBox& Bounds, bool bVisible = true);
	void Reset();
};

UCLASS(ClassGroup=(WWS), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API UMyMeshComponent : public UMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMyMeshComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
	void UpdateLocalBounds();
	//blueprint can call to create mesh section function
	UFUNCTION(BlueprintCallable, Category = "MyMeshSection")
	void CreateMeshSection(int32 Index,UStaticMesh *StaticMesh);
	UFUNCTION(BlueprintCallable, Category = "MyMeshSection")
	void ClearMeshSection(int32 Index);
	void ClearAllMeshSections();
	UFUNCTION(BlueprintCallable, Category = "MyMeshSection")
	int32 GetNumMeshSections() const;
	void SetMeshSectionVisibility(int32 Index, bool Visible);
	bool IsMeshSectionVisible(int32 Index) const;
	virtual int32 GetNumMaterials() const override;
	UFUNCTION(BlueprintCallable, Category= "MyMeshSection")
	void UpdateSectionPreTransform() const;
	UFUNCTION(BlueprintCallable, Category="MyMeshSection")
	void SetSectionPreTransform(int32 Index);
private:
	UPROPERTY(EditAnywhere)
	TArray<FMyMeshSection> Sections;

	UPROPERTY(VisibleAnywhere)
	FBoxSphereBounds LocalBounds;
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere)
	bool bShowBounds;
#endif 
	friend class FMyCustomMeshSceneProxy;
};

