#pragma once

struct Info {
	Info(int32 id, string name, SessionRef ref) : id(id), name(name), ref(ref) { }
	int32 id;
	string name;
	SessionRef ref;
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

