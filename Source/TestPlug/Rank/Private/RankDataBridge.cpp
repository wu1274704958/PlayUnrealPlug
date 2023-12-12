﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RankDataBridge.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/OutputDeviceDebug.h"
#include "Text3D/Public/Text3DComponent.h"
#include <thread>


// Sets default values for this component's properties
URankDataBridge::URankDataBridge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URankDataBridge::SetTitle(const FString& str)
{
	if(Text3D)
	{
		Text3D->GetText3DComponent()->SetText(FText::FromString(str));
	}
}

void URankDataBridge::FindAllRankItems()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("RI"), Actors);
	RankItems.AddZeroed(Actors.Num());
	for(int i = 0;i < Actors.Num();i++)
	{
		auto name = Actors[i]->GetName();
		auto idx = name[name.Len()-1] - 48;
		if(idx < RankItems.Num())
			RankItems[idx] = Actors[i];
	}
}

void URankDataBridge::CallSetData(AActor* Actor, const FString& name, int score, const FString& icon)
{
	FString cmd = FString::Printf(TEXT("SetData %s %d %s"),*name,score,*icon);//函数名字 +参数,多个参数要空格

	FOutputDeviceDebug device;

	Actor->CallFunctionByNameWithArguments(*cmd,device,NULL,true);
}




// Called when the game starts
void URankDataBridge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindAllRankItems();
#if !WITH_EDITOR
	ShowAll(false);
#endif
	m_MsgReceive.Init();
	m_MsgReceive.RegisterMsgReceiver(int64(ELocalMsgType::Settlement),this);
}

bool URankDataBridge::Parse(int64 id, const TSharedPtr<FJsonObject>& JsonObject)
{
	auto msg = std::make_unique<RankMsg>();
	msg->Title = JsonObject->GetStringField("Title");
	auto Items = JsonObject->GetArrayField("Items");
	for (int i = 0; i < Items.Num(); ++i)
	{
		RankItem item;
		item.Name = Items[i]->AsObject()->GetStringField("Name");
		item.Icon = Items[i]->AsObject()->GetStringField("Icon");
		item.Score = Items[i]->AsObject()->GetIntegerField("Score");
		msg->Items.push_back(item);
	}
	ShowAll(true);
	CallAllItemResetPos();
	SetTitle(msg->Title);
	SetItems(msg->Items);
	State = 1;
	CurrShowTime = 0.0f;
	PlayItemStartAni();
	return true;
}

void URankDataBridge::ShowAll(bool bCond)
{
	if(Text3D)
		Text3D->SetActorHiddenInGame(!bCond);
	for (int i = 0;i < RankItems.Num();i++)
	{
		RankItems[i]->SetActorHiddenInGame(!bCond);
	}
}

void URankDataBridge::SetItems(const std::vector<RankItem>& Items)
{
	int i;
	for(i = 0;i < Items.size();i++)
	{
		if(i >= RankItems.Num()) break;
		if(RankItems[i] == nullptr) continue;
		CallSetData(RankItems[i],Items[i].Name,Items[i].Score,Items[i].Icon);
	}
	for (;i < RankItems.Num();i++)
	{
		RankItems[i]->SetHidden(true);
	}
}

void URankDataBridge::PlayItemStartAni() 
{
	++PlayStartAniState;
	if(PlayStartAniState >= RankItems.Num())
	{
		PlayStartAniState = -1;
		return;
	}
	FString cmd = TEXT("PlayStartAni");//函数名字 +参数,多个参数要空格
	FOutputDeviceDebug device;
	RankItems[PlayStartAniState]->CallFunctionByNameWithArguments(*cmd,device,NULL,true);
}

void URankDataBridge::CallItemResetPos(AActor* Actor)
{
	FString cmd = TEXT("RestRootPos");//函数名字 +参数,多个参数要空格
	FOutputDeviceDebug device;
	Actor->CallFunctionByNameWithArguments(*cmd,device,NULL,true);
}

void URankDataBridge::CallStopItemStartAni(AActor* Actor)
{
	FString cmd = TEXT("StopStartAni");//函数名字 +参数,多个参数要空格
	FOutputDeviceDebug device;
	Actor->CallFunctionByNameWithArguments(*cmd,device,NULL,true);
}

void URankDataBridge::CallAllItemResetPos()
{
	for (int i = 0;i < RankItems.Num();i++)
	{
		CallStopItemStartAni(RankItems[i]);
		CallItemResetPos(RankItems[i]);
	}
}


// Called every frame
void URankDataBridge::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	switch (State)
	{
		case 0:
			{
				auto msg = m_MsgReceive.CheckHasMsg();
				if(msg < 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				break;
			}
		case 1:
			if(PlayStartAniState >= 0 && CurrShowTime >= (PlayStartAniState + 1) * PlayStartAniIntervalTime)
			{
				PlayItemStartAni();
			}
			if(CurrShowTime >= ShowTime)
			{
				ShowAll(false);
				CurrShowTime = 0.0f;
				State = 0;
			}
			CurrShowTime += DeltaTime;
			break;
	} 
}

void URankDataBridge::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	m_MsgReceive.UnInit();
}

