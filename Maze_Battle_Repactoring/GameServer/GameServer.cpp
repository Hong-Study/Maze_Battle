#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "Room.h"
#include "CreateMap.h"

int main()
{
    //윈속 초기화
    

    Room::Init();

    

    //윈속 종료
    WSACleanup();
    return 0;
}