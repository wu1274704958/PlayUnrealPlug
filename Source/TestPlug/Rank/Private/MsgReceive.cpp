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

void MsgReceive::ToWideChar(wchar_t* dst, int len, char* src)
{
	for(int i = 0;i < len;i += 2)
	{
		dst[i / 2] =  src[i + 1] << 8 | src[i];
	}
}

std::pair<int64_t,std::unique_ptr<RankMsg>> MsgReceive::CheckHasMsg()
{ 
	LPVOID lpShareMemory    = NULL;  
	std::unique_ptr<RankMsg> msg = nullptr;
	int64_t ret = -2;
	if(hFileMapping == NULL)
		Init();
	if(hFileMapping == NULL)
		return std::make_pair(-1,nullptr);
	
	lpShareMemory = MapViewOfFile(hFileMapping,  
		FILE_MAP_ALL_ACCESS,  
		0,  
		0,  
		MAX_MSG_SIZE);
	
	if (NULL != lpShareMemory && *static_cast<char*>(lpShareMemory) == 1)  
	{
		wchar_t buf[MAX_MSG_SIZE - 2] = {0};
		int n1 = MultiByteToWideChar(CP_ACP, 0,
		static_cast<char*>(lpShareMemory) + 2, strlen(static_cast<char*>(lpShareMemory) + 2), buf, MAX_MSG_SIZE - 2);
		FString fstr(buf);
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
		for(int i = 0;i < MAX_MSG_SIZE;++i)
		{
			static_cast<char*>(lpShareMemory)[i] = 0;
		}
		if (NULL != lpShareMemory)      UnmapViewOfFile(lpShareMemory);  
		return std::make_pair(0,std::move(msg));
	}
	if(NULL == lpShareMemory)
		ret = GetLastError();
	if (NULL != lpShareMemory)      UnmapViewOfFile(lpShareMemory);  
	return std::make_pair(ret, nullptr);
}
