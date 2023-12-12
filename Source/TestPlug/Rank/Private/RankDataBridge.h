// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Text3D/Public/Text3DActor.h"
#include "MsgReceive.h"
#include "RankDataBridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API URankDataBridge : public UActorComponent , public ILocalMemMsg
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URankDataBridge();

protected:
	void SetTitle(const FString& str);
	void FindAllRankItems();
	void CallSetData(AActor* Actor,const FString& name,int score,const FString& icon);
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual bool Parse(int64 id, const TSharedPtr<FJsonObject>& JsonObject) override;

public:
	void ShowAll(bool bCond);
	void SetItems(const std::vector<RankItem>& Items);
	void PlayItemStartAni();
	static void CallItemResetPos(AActor* Actor);
	static void CallStopItemStartAni(AActor* Actor);
	void CallAllItemResetPos();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	UPROPERTY(VisibleAnywhere, Category = "Rank")
	TArray<AActor*> RankItems;

	UPROPERTY(EditAnywhere,Category="Rank")
	AText3DActor* Text3D;

	const float ShowTime = 9.0f;
	float CurrShowTime = 0.0f;
	int State = 0;
	
	const float PlayStartAniIntervalTime = 0.5f;
	int PlayStartAniState = -1;

	MsgReceive m_MsgReceive;
};
