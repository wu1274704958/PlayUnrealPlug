#pragma once
#include "memory"
#include "vector"
#include "Core/Public/Containers/UnrealString.h"

struct RankItem
{
	FString Name;
	FString Icon;
	int Score;
};
struct RankMsg 
{
	FString Title;
	std::vector<RankItem> Items;
};

class MsgReceive
{
private:
public:
	std::pair<int64_t,std::unique_ptr<RankMsg>> CheckHasMsg();
	
};
