#include "pch.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"
#include "PacketHandler.h"

ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

void ServerSession::OnConnected()
{
	//HANDLER->MakeSendBuffer(S_GameLogin)
}

void ServerSession::OnDisconnected()
{
}

int32 ServerSession::OnSend(BYTE* buffer, int32 len)
{
	
	return len;
}

int32 ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	if (HANDLER->Dispatch(buffer, len, shared_from_this()) == false)
		return SOCKET_ERROR;

	return len;
}