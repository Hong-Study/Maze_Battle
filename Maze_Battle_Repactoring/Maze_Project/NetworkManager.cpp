#include "pch.h"
#include "NetworkManager.h"
#include "service.h"

function<SessionRef(void)> factory = make_shared<GameSession>;

void NetworkManager::Init(int users)
{
	SocketUtils::Init();

	service = make_shared<ClientService>(Address(L"127.0.0.1", 5000), factory);

	service->Connect(users);

	service->Start();
}

void NetworkManager::Start()
{
	THREAD->Push([=]() {
		service->Start();
		});
}
