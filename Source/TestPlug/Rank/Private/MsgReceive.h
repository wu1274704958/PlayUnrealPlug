#pragma once
#include "memory"
#include "vector"
#include "Windows/WindowsWindow.h"

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
	HANDLE hFileMapping = NULL;
public:
	bool Init();
	void UnInit();
	static void ToWideChar(wchar_t* dst, int len, char* src);
	std::pair<int64_t,std::unique_ptr<RankMsg>> CheckHasMsg();
	
};
