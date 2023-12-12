// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGroupBridge.h"

#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceDebug.h"
#include "Rank/PlayerGroupUIBase.h"
#include "Rank/Private/RankDataBridge.h"

// Sets default values for this component's properties
UPlayerGroupBridge::UPlayerGroupBridge()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UPlayerGroupBridge::GroupWidgetCall(FString cmd)
{
	FOutputDeviceDebug device;
	PlayerGroupWidget->CallFunctionByNameWithArguments(*cmd,device,NULL,true);
}


// Called when the game starts
void UPlayerGroupBridge::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(PlayerGroupWidgetClass)
	{
		PlayerGroupWidget = CreateWidget<UUserWidget>(GetWorld(),PlayerGroupWidgetClass);
		PlayerGroupWidget->AddToViewport();
	}

	auto bridge = GetOwner()->GetComponentByClass(URankDataBridge::StaticClass());
	if(bridge)
	{
		auto rankData = Cast<URankDataBridge>(bridge);
		auto tableUI = Cast<UPlayerGroupUIBase>(PlayerGroupWidget);
		rankData->m_MsgReceive.RegisterMsgReceiver(static_cast<int64>(ELocalMsgType::AddPlayer),tableUI);
		rankData->m_MsgReceive.RegisterMsgReceiver(static_cast<int64>(ELocalMsgType::ClearAllPlayer),tableUI);
		rankData->m_MsgReceive.RegisterMsgReceiver(static_cast<int64>(ELocalMsgType::UpdatePlayerGold),tableUI);
	}
}


// Called every frame
void UPlayerGroupBridge::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

