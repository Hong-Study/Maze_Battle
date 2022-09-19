#pragma once
#include "pch.h"
#include "CreateMap.h"

class Room
{
public:
	static void Init();
	
	static bool PushHost(int Index);
	static bool PushClient(int Who, int Index);
	static bool DeleteHost(int Index);
	static bool DeleteClient(int Index);
	static bool CheckIndex(int Index);

	static int GetHostIndex(int Index) { return HostRoom[Index]; }
	static int GetClientIndex(int Index) { return ClientRoom[Index]; }
	static int GetHostSize() { return HostRoom.size(); }
	static int GetCientSize() { return ClientSize; }

private:
	static vector<int> HostRoom;
	static int ClientRoom[WSA_MAXIMUM_WAIT_EVENTS];
	static int ClientSize;

public:
	static CreateMap* GameMaps[WSA_MAXIMUM_WAIT_EVENTS];
};