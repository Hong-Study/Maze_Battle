#include "pch.h"
#include "GameSession.h"

GameSession::GameSession()
{
}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
}

void GameSession::OnDisconnected()
{
}

int32 GameSession::OnSend(const BYTE* buffer, int32 len)
{
	return int32();
}

int32 GameSession::OnRecv(BYTE* buffer, int32 len)
{
	return int32();
}
