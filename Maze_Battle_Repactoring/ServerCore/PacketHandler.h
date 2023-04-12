#pragma once

class PacketHandler
{
	using Func = std::function<bool(shared_ptr<PacketHandler>, BYTE*, uint32, SessionRef)>;

public:
	void Init();
	bool Dispatch(BYTE* buffer, uint32 len, SessionRef ref);

private:
	virtual bool HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref) { return false; };
	virtual bool HandlerLogin(BYTE* buffer, uint32 len, SessionRef ref) { return false; };

private:
	Func func[(int)PKT_TYPE::COUNT];
};