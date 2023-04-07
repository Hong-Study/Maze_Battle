#pragma once
#include "GameSession.h"

class NetworkManager
{
	SINGLETON(NetworkManager)

public:
	void Init(int users);
	void Start();

	ClientServiceRef GetService() { return service; }

private:
	ClientServiceRef service;
};


