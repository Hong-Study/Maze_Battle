#pragma once
#include "Room.h"

class RoomManager
{
	SINGLETON(RoomManager)

public:
	void Init();

	shared_ptr<Room> PushHost(int32 id, string name, SessionRef ref, uint8 mapLevel);
	shared_ptr<Room> PushClient(int32 index, int32 id, string name, SessionRef ref);
	bool DeleteHost(int32 index);
	bool ExitClient(int32 index, int32 id);
	bool CheckIndex(int32 index);

	shared_ptr<Room>			GetRoomIndex(int32 index) { return _rooms[index]; };
private:
	map<int32, shared_ptr<Room>> _rooms;
};