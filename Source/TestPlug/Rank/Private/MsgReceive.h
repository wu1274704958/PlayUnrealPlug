#pragma once
#include "memory"
#include "vector"
#include "Windows/WindowsWindow.h"
#include "unordered_map"


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

enum class ELocalMsgType : short
{
	None = 0,
	Settlement = 1,
	AddPlayer = 2,
	ClearAllPlayer = 3,
	UpdatePlayerGold = 4,
	ShowPlayerAction = 5,
	RemoveGroup = 6
};

class ILocalMemMsg
{
public:
	virtual ~ILocalMemMsg() {}
	virtual bool Parse(int64 id,const TSharedPtr<FJsonObject>& JsonObject) = 0;
};

class MsgReceive
{
private:
	HANDLE hFileMapping = NULL;
	std::unordered_map<int64,ILocalMemMsg*> MsgTable;
public:
	bool Init();
	void UnInit();
	bool RegisterMsgReceiver(int64 id,ILocalMemMsg* pMsg);
	void UnRegisterMsgReceiver(int64 id);
	void OnNotifyMsg(int64 id,const TSharedPtr<FJsonObject>& JsonObject);
	int64_t CheckHasMsg();
};
