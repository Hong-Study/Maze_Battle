#pragma once
#include "pch.h"

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

class Room
{
public:
	Room(Info host, uint8 mapLevel);
	~Room() { _gameMap = nullptr; }

	bool		SetClinetInfo(Info client);
	bool		DeleteRoom();
	void		CleanClient();

	int32		GetHostId() { return _hostInfo->id; }
	string		GetHostName() { return _hostInfo->name; }
	SessionRef	GetHostRef() { return _hostInfo->ref; }

	int32		GetClientId() { return _clientInfo->id; }
	string		GetClientName() { return _clientInfo->name; }
	SessionRef	GetClientRef() { return _clientInfo->ref; }

private:
	shared_ptr<class MapInfo> _gameMap;
	Info* _hostInfo;
	Info* _clientInfo;
};

struct Info {
	Info(int32 id, string name, SessionRef ref) : id(id), name(name), ref(ref) { }
	int32 id;
	string name;
	SessionRef ref;
};