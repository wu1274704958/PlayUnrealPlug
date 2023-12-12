// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Private/Rank/PlayerGroupItemData.h"
#include "Private/MsgReceive.h"
#include "PlayerGroupUIBase.generated.h"


UCLASS()
class UIconMaterialData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UTexture2DDynamic* Texture = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* Material = nullptr;
	int State = 0;
	UIconMaterialData()
	{
		State = 1;
	}
};
/**
 * 
 */
UCLASS(Blueprintable)
class TESTPLUG_API UPlayerGroupUIBase : public UUserWidget,public ILocalMemMsg
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable)
	void SortData();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UListView* GetListView();
	virtual UListView* GetListView_Implementation();
	UFUNCTION(BlueprintCallable)
	void OnShow();
	virtual bool Parse(int64 id, const TSharedPtr<FJsonObject>& JsonObject) override;
public:
	UFUNCTION(BlueprintCallable)
	void ClearList();
	UFUNCTION(BlueprintCallable)
	UPlayerGroupItemData* AddPlayer(int64 id, FString name, FString icon, int score, int gold, int group,UMaterialInstanceDynamic* iconMat);
	UFUNCTION(BlueprintCallable)
	void RemovePlayerByGroup(int group);
	UFUNCTION(BlueprintCallable)
	void UpdateGold(int64 id, int gold);
	UFUNCTION(BlueprintCallable)
	void UpdateListView(bool sort = true,bool setData = true);
	bool HasIcon(const FString& icon);
	bool IsIconDownloading(const FString& icon);
	bool IsDownloadFailed(const FString& icon);
	void DownloadIcon(const FString& icon,UPlayerGroupItemData* item);
	UMaterialInstanceDynamic* GetIconMaterial(const FString& icon);
	UMaterialInstanceDynamic* CreateDynIconMaterial(UTexture2DDynamic* Texture);

protected:
	UPROPERTY(EditAnywhere)
	TArray<UPlayerGroupItemData*> PlayerGroupItems;
	UPROPERTY(EditAnywhere)
	UMaterial* IconMaterial;
	UListView* m_ListView;
	UPROPERTY()
	TMap<FString,UIconMaterialData*> IconMap;
};
