#pragma once
#include <Session.h>

class ServerSession : public PacketSession
{
	using Super = Session;
public:
	ServerSession();
	virtual ~ServerSession();

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual int32 OnSend(BYTE* buffer, int32 len) override;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override;
};


