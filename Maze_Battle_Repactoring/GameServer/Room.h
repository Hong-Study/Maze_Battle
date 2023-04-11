#pragma once
#include "pch.h"

class Room
{
	SINGLETON(Room)

public:
	void Init();
	
	bool PushHost(int32 index);
	bool PushClient(int32 who, int32 index);
	bool DeleteHost(int32 index);
	bool CheckIndex(int32 index);

	shared_ptr<class MapInfo> GetMapIndex(int32 index);

private:
	map<int32, int32> _rooms;
	map<int32, shared_ptr<class MapInfo>> _gameMaps;
};