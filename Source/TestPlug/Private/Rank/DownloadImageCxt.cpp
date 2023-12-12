// Fill out your copyright notice in the Description page of Project Settings.


#include "Rank/DownloadImageCxt.h"
#include "Engine/Texture2DDynamic.h"
#include "Blueprint/AsyncTaskDownloadImage.h"

void UDownloadImageCxt::OnGetTexture2D(UTexture2DDynamic* Texture)
{
	if(OnSuccess)
		OnSuccess(Url,Texture);
}

void UDownloadImageCxt::OnGetTexture2DFailed(UTexture2DDynamic* Texture)
{
	if(OnFailed)
		OnFailed(Url);
}

void UDownloadImageCxt::Download(const FString& URL, std::function<void(const FString&, UTexture2DDynamic*)> _OnSuccess,
                                 std::function<void(const FString&)> _OnFailed)
{
	this->Url = URL;
	this->OnSuccess = std::move(_OnSuccess);
	this->OnFailed = std::move(_OnFailed);
	UAsyncTaskDownloadImage* mDownloadTask = NewObject<UAsyncTaskDownloadImage>();
	mDownloadTask->OnSuccess.AddDynamic(this, &UDownloadImageCxt::OnGetTexture2D);
	mDownloadTask->OnFail.AddDynamic(this, &UDownloadImageCxt::OnGetTexture2DFailed);
	mDownloadTask->Start(URL);
}
