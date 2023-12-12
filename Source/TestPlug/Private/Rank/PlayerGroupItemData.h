// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerGroupItemData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TESTPLUG_API UPlayerGroupItemData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int64 Id;
	UPROPERTY(BlueprintReadWrite)
	FString Name;
	UPROPERTY(BlueprintReadWrite)
	FString Icon;
	UPROPERTY(BlueprintReadWrite)
	int Score;
	UPROPERTY(BlueprintReadWrite)
	int Gold;
	UPROPERTY(BlueprintReadWrite)
	int Group;
	UPROPERTY(BlueprintReadOnly)
	UMaterialInstanceDynamic* IconMaterial;
public:
	UFUNCTION(BlueprintCallable)
	void SetData(int64 _id, FString _name, FString _icon, int _score, int _gold, int _group);
	
};
