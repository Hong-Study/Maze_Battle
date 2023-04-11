#include "pch.h"
#include "Room.h"
#include "ObjectPool.h"
#include "MapInfo.h"

//초기화
void Room::Init()
{
   
}

//방 생성시
bool Room::PushHost(int32 index)
{
    if (CheckIndex(index))
        return false;

    _rooms[index] = -1;
    _gameMaps[index] = ObjectPool<MapInfo>::MakeShared(10);
    return true;
}

//방 입장시
bool Room::PushClient(int32 who, int32 index)
{
    if (!CheckIndex(index))
        return false;
    _rooms[index] = who;
    return true;
}

//방 삭제시
bool Room::DeleteHost(int32 index)
{
    if (!CheckIndex(index))
        return false;

    _rooms.erase(index);

    _gameMaps[index] = nullptr;
    _gameMaps.erase(index);
    return true;
}

bool Room::CheckIndex(int32 index)
{
    if (_rooms.find(index) == _rooms.end())
        return false;
    
    return true;
}

shared_ptr<class MapInfo> Room::GetMapIndex(int32 index)
{
    if (!CheckIndex(index))
        return nullptr;
   
    return _gameMaps[index];
}
