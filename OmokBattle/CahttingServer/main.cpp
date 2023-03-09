#include "pch.h"
#include <Service.h>
#include "ChattingSession.h"

function<SessionRef(void)> factory = make_shared<ChattingSession>;
int main()
{	
	SocketUtils::Init();

	ServerServiceRef service = make_shared<ServerService>(Address(L"127.0.0.1", 5000), factory);

	service->Listen();

	service->Start();
}