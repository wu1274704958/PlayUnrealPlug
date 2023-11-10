// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Text3D/Public/Text3DActor.h"
#include "MsgReceive.h"
#include "RankDataBridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPLUG_API URankDataBridge : public UActorComponent
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

public:
	void ShowAll(bool bCond);
	void SetItems(const std::vector<RankItem>& Items);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, Category = "Rank")
	TArray<AActor*> RankItems;

	UPROPERTY(EditAnywhere,Category="Rank")
	AText3DActor* Text3D;

	const float ShowTime = 6.0f;
	float CurrShowTime = 0.0f;
	int State = 0;

	MsgReceive m_MsgReceive;
};
