// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGroupUIBase.h"

#include "Engine/Texture2D.h"
#include "Engine/Texture2DDynamic.h"
#include "Rank/DownloadImageCxt.h"

void UPlayerGroupUIBase::SortData()
{
	PlayerGroupItems.Sort([](const UPlayerGroupItemData& a, const UPlayerGroupItemData& b) {
		if(a.Group == b.Group)
			return a.Id < b.Id;
		return a.Group < b.Group;
	});
}

void UPlayerGroupUIBase::OnShow()
{
	m_ListView = GetListView();
}

bool UPlayerGroupUIBase::Parse(int64 id, const TSharedPtr<FJsonObject>& JsonObject)
{
	switch ((ELocalMsgType)id)
	{
	case ELocalMsgType::AddPlayer:
		{
			auto icon= JsonObject->GetStringField("Icon");
			auto item = AddPlayer((int64)JsonObject->GetNumberField("Id"),
				JsonObject->GetStringField("Name"),
				icon,
				(int)JsonObject->GetNumberField("Score"),
				0,
				(int)JsonObject->GetNumberField("Group"),
				GetIconMaterial(icon));
			if(!IconMap.Contains(icon))
			{
				DownloadIcon(icon,item);
			}
		}
		break;
	case ELocalMsgType::ClearAllPlayer:
		ClearList();
		break;
	case ELocalMsgType::UpdatePlayerGold:
		{
			auto items = JsonObject->GetArrayField("Items");
			for(int i = 0;i < items.Num();i++)
			{
				UpdateGold((int64)items[i]->AsObject()->GetNumberField("Id"),
					(int)items[i]->AsObject()->GetNumberField("Gold"));
			}
			UpdateListView(false);
		}
		break;
	case ELocalMsgType::ShowPlayerAction:
		break;
	case ELocalMsgType::RemoveGroup:
		break;
	}
	return true;
}

void UPlayerGroupUIBase::ClearList()
{
	PlayerGroupItems.Empty();
	m_ListView->ClearListItems();
}

UPlayerGroupItemData* UPlayerGroupUIBase::AddPlayer(int64 id, FString name, FString icon, int score, int gold, int group,UMaterialInstanceDynamic* iconMat)
{
	auto item = NewObject<UPlayerGroupItemData>();
	item->IconMaterial = iconMat;
	item->SetData(id, std::move(name), std::move(icon), score, gold, group);
	PlayerGroupItems.Add(item);
	UpdateListView();
	return item;
}

void UPlayerGroupUIBase::RemovePlayerByGroup(int group)
{
	for(int i = PlayerGroupItems.Num() - 1;i >= 0;)
	{
		if(PlayerGroupItems[i]->Group == group)
		{
			PlayerGroupItems.RemoveAt(i);
		}
		else
		{
			--i;
		}
	}
	UpdateListView(false,false);
}

void UPlayerGroupUIBase::UpdateGold(int64 id, int gold)
{
	for(int i = 0;i < PlayerGroupItems.Num();i++)
	{
		if(PlayerGroupItems[i]->Id == id)
		{
			PlayerGroupItems[i]->Gold = gold;
			break;
		}
	}
}

void UPlayerGroupUIBase::UpdateListView(bool sort,bool setData)
{
	if(sort)SortData();
	if(setData) m_ListView->SetListItems(PlayerGroupItems);
	m_ListView->RegenerateAllEntries();
}

bool UPlayerGroupUIBase::HasIcon(const FString& icon)
{
	return IconMap.Contains(icon) && IconMap[icon]->State == 2;
}

bool UPlayerGroupUIBase::IsIconDownloading(const FString& icon)
{
	return IconMap.Contains(icon) && IconMap[icon]->State == 1;
}

bool UPlayerGroupUIBase::IsDownloadFailed(const FString& icon)
{
	return IconMap.Contains(icon) && IconMap[icon]->State == 0;
}

void UPlayerGroupUIBase::DownloadIcon(const FString& icon,UPlayerGroupItemData* data)
{
	IconMap.Add(icon, NewObject<UIconMaterialData>(this));
	auto cxt = NewObject<UDownloadImageCxt>();
	cxt->Download(icon,[this,icon,data](const FString& url, UTexture2DDynamic* texture){
		IconMap[icon]->Texture = texture;
		auto material = CreateDynIconMaterial(texture);
		IconMap[icon]->Material = material;
		IconMap[icon]->State = 2;
		data->IconMaterial = material;
	},[this,icon](const FString& url){
		IconMap[icon]->State = 0;
	});
}

UMaterialInstanceDynamic* UPlayerGroupUIBase::CreateDynIconMaterial(UTexture2DDynamic* Texture)
{
	UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(IconMaterial, this);
	material->SetTextureParameterValue("Src", Texture);
	return material;
}

UMaterialInstanceDynamic* UPlayerGroupUIBase::GetIconMaterial(const FString& icon)
{
	if(IconMap.Contains(icon))
		return IconMap[icon]->Material;
	return nullptr;
}

UListView* UPlayerGroupUIBase::GetListView_Implementation()
{
	return nullptr;
}


