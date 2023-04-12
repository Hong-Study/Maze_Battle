#include "pch.h"
#include "MapInfo.h"
#include "PacketHandler.h"
#include "ServerSession.h"
#include "Service.h"

function<SessionRef(void)> factory = make_shared<ServerSession>;
int main()
{
    //윈속 초기화
    SocketUtils::Init();

    ServerServiceRef service = make_shared<ServerService>(Address(L"127.0.0.1", 5000), factory);

    service->Listen();

    service->Start();
    
    //윈속 종료
    WSACleanup();
    return 0;
}