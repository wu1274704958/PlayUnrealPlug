// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "functional"
#include "DownloadImageCxt.generated.h"

/**
 * 
 */
UCLASS()
class TESTPLUG_API UDownloadImageCxt : public UObject
{
	GENERATED_BODY()

public:
	FString Url;
	std::function<void(const FString&,UTexture2DDynamic*)> OnSuccess;
	std::function<void(const FString&)> OnFailed;
public:
	UFUNCTION()
	void OnGetTexture2D(UTexture2DDynamic* Texture);
	UFUNCTION()
	void OnGetTexture2DFailed(UTexture2DDynamic* Texture);
	void Download(const FString& URL,std::function<void(const FString&,UTexture2DDynamic*)> OnSuccess,std::function<void(const FString&)> OnFailed);
};
