#pragma once
#include <Session.h>

class GameSession : public Session
{
public:
	GameSession();
	virtual ~GameSession();

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual int32 OnSend(const BYTE* buffer, int32 len) override;
	virtual int32 OnRecv(BYTE* buffer, int32 len) override;
};
