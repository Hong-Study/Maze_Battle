#include "pch.h"
#include "Room.h"
#include "MapInfo.h"

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
