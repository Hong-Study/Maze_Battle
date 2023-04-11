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

int32 GameSession::OnSend(BYTE* buffer, int32 len)
{
	return int32();
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	return int32();
}
