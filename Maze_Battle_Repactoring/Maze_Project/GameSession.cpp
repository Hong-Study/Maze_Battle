#include "pch.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "PacketHandler.h"

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
	return len;
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	if (HANDLER->Dispatch(buffer, len, shared_from_this()) == false)
		return SOCKET_ERROR;

	return len;
}
