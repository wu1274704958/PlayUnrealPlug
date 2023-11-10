#include "MsgReceive.h"
#include "Windows/WindowsWindow.h"

#define MUTEX_NAME L"SM_Mutex"
#define FILE_MAP_NAME L"FM_RANK_MSG"
#define MAX_MSG_SIZE 4096 * 4
#define FALSE 0

std::pair<int64_t,std::unique_ptr<RankMsg>> MsgReceive::CheckHasMsg()
{
	HANDLE hMutex           = NULL;  
	HANDLE hFileMapping     = NULL;  
	LPVOID lpShareMemory    = NULL;  
	HANDLE hServerWriteOver = NULL;  
	HANDLE hClientReadOver  = NULL;  
	std::unique_ptr<RankMsg> msg = nullptr;
	int64_t ret = 0;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS,  
		FALSE,  
		MUTEX_NAME);
	if (NULL == hMutex)  
	{
		ret = GetLastError();
		goto END;
	}
	if (WaitForSingleObject(hMutex, 30) != WAIT_OBJECT_0) //hMutex 一旦互斥对象处于有信号状态，则该函数返回  
	{
		ret = GetLastError();
		goto END;
	}
	hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,  
		FALSE,  
		FILE_MAP_NAME);  
	if (NULL == hFileMapping)  
	{  
		ret = GetLastError();
		goto END;
	}  
  
	lpShareMemory = MapViewOfFile(hFileMapping,  
		FILE_MAP_ALL_ACCESS,  
		0,  
		0,  
		MAX_MSG_SIZE);  
	if (NULL != lpShareMemory)  
	{  
		FString fstr(UTF8_TO_TCHAR(static_cast<char*>(lpShareMemory)));
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(fstr);
		if(!FJsonSerializer::Deserialize(Reader,JsonObject))
		{
			return std::make_pair(-1,nullptr);
		}
		msg = std::make_unique<RankMsg>();
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
		return std::make_pair(0,std::move(msg));
	}else
	{
		ret = GetLastError();
	}
	
END:
	//release share memory  
	if (NULL != hServerWriteOver)   CloseHandle(hServerWriteOver);  
	if (NULL != hClientReadOver)    CloseHandle(hClientReadOver);  
	if (NULL != lpShareMemory)      UnmapViewOfFile(lpShareMemory);  
	if (NULL != hFileMapping)       CloseHandle(hFileMapping);  
	if (NULL != hMutex)             ReleaseMutex(hMutex); 
	return std::make_pair(ret, nullptr);
}
