#pragma once
#include <Session.h>

struct Loby_Data {
	PlayerState Type;
	uint16 Level;
	uint16 RoomNumber;
	bool GameStart;
	bool Win;
	std::string name;
};

class ServerSession : public Session
{
	using Super = Session;
public:
	ServerSession();
	virtual ~ServerSession();

	virtual void OnConnected() override;
	virtual void OnDisconnected() override;
	virtual int32 OnSend(const BYTE* buffer, int32 len) override;
	virtual int32 OnRecv(BYTE* buffer, int32 len) override;
};


