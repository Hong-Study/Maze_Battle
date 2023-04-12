#pragma once
#include "PacketHandler.h"

class ServerPacketHandler : public PacketHandler
{
	SINGLETON(ServerPacketHandler)

private:
	virtual bool HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref) override;
	virtual bool HandlerLogin(BYTE* buffer, uint32 len, SessionRef ref) override;

public:
	template<typename T>
	SendBufferRef MakeSendBuffer(T&& data, PKT_TYPE type);

	template<>
	SendBufferRef MakeSendBuffer(S_LobyInside&& data, PKT_TYPE type);
};

template<typename T>
inline SendBufferRef ServerPacketHandler::MakeSendBuffer(T&& data, PKT_TYPE type)
{
	SendBufferRef ref = SENDBUF->Open(4096);
	BufferWriter w(ref->Data(), ref->GetSize());

	PacketHeader* head = w.Reserve<PacketHeader>;
	w << (T)data;

	head->size = w.WriteSize();
	head->type = type;

	return ref;
}

template<>
inline SendBufferRef ServerPacketHandler::MakeSendBuffer(S_LobyInside&& data, PKT_TYPE type)
{
	return SendBufferRef();
}