#include "pch.h"
#include "Room.h"

vector<int> Room::HostRoom;
int Room::ClientRoom[WSA_MAXIMUM_WAIT_EVENTS];
int Room::ClientSize = 0;
CreateMap* Room::GameMaps[WSA_MAXIMUM_WAIT_EVENTS];
//초기화
void Room::Init()
{
    fill_n(ClientRoom, WSA_MAXIMUM_WAIT_EVENTS, -1);
}

//방 생성시
bool Room::PushHost(int Index)
{
    if (HostRoom.size() >= WSA_MAXIMUM_WAIT_EVENTS || Index >= WSA_MAXIMUM_WAIT_EVENTS)
        return false;
    HostRoom.push_back(Index);
    return true;
}

//방 입장시
bool Room::PushClient(int Who, int Index)
{
    if (ClientSize >= WSA_MAXIMUM_WAIT_EVENTS || Index >= WSA_MAXIMUM_WAIT_EVENTS)
        return false;
    ClientRoom[Who] = Index;
    ++ClientSize;
    return true;
}

//방 삭제시
bool Room::DeleteHost(int Index)
{
    if (Index > HostRoom.size())
        return false;
    if (HostRoom[Index] == -1)
        return false;
    HostRoom.erase(HostRoom.begin() + Index);
    DeleteClient(Index);

    return true;
}

//방 나갈때
bool Room::DeleteClient(int Index)
{
    if (ClientRoom[Index] == -1)
        return false;
    ClientRoom[Index] = -1;
    --ClientSize;
    return true;
}

bool Room::CheckIndex(int Index)
{
    if(Index >= HostRoom.size())
        return false;
    
    return true;
}
