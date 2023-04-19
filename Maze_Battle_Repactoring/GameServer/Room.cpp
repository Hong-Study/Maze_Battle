#include "pch.h"
#include "Room.h"
#include "ObjectPool.h"
#include "MapInfo.h"

//초기화
void RoomManager::Init()
{
   
}

//방 생성시
shared_ptr<Room> RoomManager::PushHost(int32 id, string name, SessionRef ref, uint8 mapLevel)
{
    if (!CheckIndex(id))
        return nullptr;

    _rooms[id] = ObjectPool<Room>::MakeShared(Info{ id, name, ref }, mapLevel);
    return _rooms[id];
}

//방 입장시
shared_ptr<Room> RoomManager::PushClient(int32 index, int32 id, string name, SessionRef ref)
{
    if (!CheckIndex(index))
        return nullptr;

    _rooms[index]->SetClinetInfo(Info{ id, name, ref });

    return _rooms[index];
}

bool RoomManager::DeleteHost(int32 index)
{
    if (_rooms[index]->DeleteRoom()) {
        _rooms.erase(index);
        return true;
    }

    return false;
}

bool RoomManager::ExitClient(int32 index, int32 id)
{
    if (_rooms[index]->GetClientId() == id)
    {
        _rooms[index]->CleanClient();
        return true;
    }

    return false;
}

bool RoomManager::CheckIndex(int32 index)
{
    if (_rooms.find(index) == _rooms.end())
        return false;

    return true;
}

Room::Room(Info host, uint8 mapLevel)
{
    _gameMap = ObjectPool<MapInfo>::MakeShared(mapLevel);
    _hostInfo = xnew<Info>(host.id, host.name, host.ref);
    _clientInfo = nullptr;
}

bool Room::SetClinetInfo(Info client)
{
    if (_clientInfo != nullptr)
        return false;

    _clientInfo = xnew<Info>(client.id, client.name, client.ref );

    return true;
}

bool Room::DeleteRoom()
{
    if (_hostInfo != nullptr)
    {
        // TODO ref Send
    }
    if (_clientInfo != nullptr)
    {
        // TODO ref Send
    }

    return true;
}

void Room::CleanClient()
{
    if (_clientInfo != nullptr) {
        // TODO
        xdelete(_clientInfo);
    }

    _clientInfo = nullptr;
}
