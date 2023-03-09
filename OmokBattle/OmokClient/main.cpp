#include "pch.h"
#include <Service.h>
#include "DummySession.h"

function<SessionRef(void)> factory = make_shared<DummySession>;
int main()
{
	SocketUtils::Init();

	ClientServiceRef service = make_shared<ClientService>(Address(L"127.0.0.1", 5000), factory);

	service->Init(1);

	service->Start();
}