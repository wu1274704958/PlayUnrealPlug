#include "MsgReceive.h"

#define MUTEX_NAME L"SM_Mutex"
#define FILE_MAP_NAME L"FM_RANK_MSG"
#define MAX_MSG_SIZE 4096 * 4
#define FALSE 0

bool MsgReceive::Init()
{
	hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,  
		FILE_MAP_NAME);  
	if (NULL == hFileMapping)  
	{  
		return false;
	}
	return true;
}

void MsgReceive::UnInit()
{
	if (NULL != hFileMapping)       CloseHandle(hFileMapping);  
}

bool MsgReceive::RegisterMsgReceiver(int64 id, ILocalMemMsg* pMsg)
{
	if(MsgTable.find(id) != MsgTable.end())
		return false;
	MsgTable[id] = pMsg;
	return true;
}

void MsgReceive::UnRegisterMsgReceiver(int64 id)
{
	MsgTable.erase(id);
}

void MsgReceive::OnNotifyMsg(int64 id, const TSharedPtr<FJsonObject>& JsonObject)
{
	if(MsgTable.find(id) != MsgTable.end())
		MsgTable[id]->Parse(id,JsonObject);
}

int64_t MsgReceive::CheckHasMsg()
{ 
	LPVOID lpShareMemory    = NULL;  
	std::unique_ptr<RankMsg> msg = nullptr;
	int64_t ret = -2;
	if(hFileMapping == NULL)
		Init();
	if(hFileMapping == NULL)
	{
		ret = -1;
		goto END;
	}
	
	lpShareMemory = MapViewOfFile(hFileMapping,  
		FILE_MAP_ALL_ACCESS,  
		0,  
		0,  
		MAX_MSG_SIZE);
	
	if (NULL != lpShareMemory && *static_cast<char*>(lpShareMemory) == 1)  
	{
		auto id = (short*)(static_cast<char*>(lpShareMemory) + 1);
		constexpr int Offset = 3;
		wchar_t buf[MAX_MSG_SIZE - Offset] = {0};
		int n1 = MultiByteToWideChar(CP_ACP, 0,
		static_cast<char*>(lpShareMemory) + Offset, strlen(static_cast<char*>(lpShareMemory) + Offset), buf, MAX_MSG_SIZE - Offset);
		FString fstr(buf);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(fstr);
		if(!FJsonSerializer::Deserialize(Reader,JsonObject))
		{
			ret = -3;
			goto END;
		}
		OnNotifyMsg(*id,JsonObject);
		memset(lpShareMemory,0,MAX_MSG_SIZE);
		ret = 0;
	}
	END:
	if(NULL == lpShareMemory)
		ret = GetLastError();
	if (NULL != lpShareMemory)
		UnmapViewOfFile(lpShareMemory);  
	return ret;
}
