#pragma once
#include <Session.h>

class GameSession : public PacketSession
{
public:
	GameSession();
	virtual ~GameSession();

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual int32 OnSend(BYTE* buffer, int32 len) override;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override;
};
