// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGroupItemData.h"


void UPlayerGroupItemData::SetData(int64 _id, FString _name, FString _icon, int _score, int _gold, int _group)
{
	Id = _id;
	Name = std::move(_name);
	Icon = std::move(_icon);
	Score = _score;
	Gold = _gold;
	Group = _group;
}
