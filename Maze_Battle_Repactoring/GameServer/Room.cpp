#include "pch.h"
#include "Room.h"

vector<int> Room::HostRoom;
int Room::ClientRoom[WSA_MAXIMUM_WAIT_EVENTS];
int Room::ClientSize = 0;
CreateMap* Room::GameMaps[WSA_MAXIMUM_WAIT_EVENTS];
//�ʱ�ȭ
void Room::Init()
{
    fill_n(ClientRoom, WSA_MAXIMUM_WAIT_EVENTS, -1);
}

//�� ������
bool Room::PushHost(int Index)
{
    if (HostRoom.size() >= WSA_MAXIMUM_WAIT_EVENTS || Index >= WSA_MAXIMUM_WAIT_EVENTS)
        return false;
    HostRoom.push_back(Index);
    return true;
}

//�� �����
bool Room::PushClient(int Who, int Index)
{
    if (ClientSize >= WSA_MAXIMUM_WAIT_EVENTS || Index >= WSA_MAXIMUM_WAIT_EVENTS)
        return false;
    ClientRoom[Who] = Index;
    ++ClientSize;
    return true;
}

//�� ������
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

//�� ������
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
