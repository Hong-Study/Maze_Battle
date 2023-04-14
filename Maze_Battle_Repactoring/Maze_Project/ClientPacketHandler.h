#pragma once
#include "PacketHandler.h"

class ClientPacketHandler : public PacketHandler
{
	SINGLETON(ClientPacketHandler)

private:
	virtual bool HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref) override;
	virtual bool HandlerLogin(BYTE* buffer, uint32 len, SessionRef ref) override;

public:
	template<typename T>
	SendBufferRef MakeSendBuffer(T&& data, PKT_TYPE type);

	template<>
	SendBufferRef MakeSendBuffer(C_RoomCreate&& data, PKT_TYPE type);
};

template<typename T>
inline SendBufferRef ClientPacketHandler::MakeSendBuffer(T&& data, PKT_TYPE type)
{
	SendBufferRef ref = SENDBUF->Open(4096);
	BufferWriter w(ref->Data(), ref->GetSize());

	PacketHeader* head = w.Reserve<PacketHeader>();
	w << (T)data;

	head->size = w.WriteSize();
	head->type = type;
	ref->Close(w.WriteSize());

	return ref;
}

template<>
inline SendBufferRef ClientPacketHandler::MakeSendBuffer(C_RoomCreate&& data, PKT_TYPE type)
{
	SendBufferRef ref = SENDBUF->Open(4096);
	BufferWriter w(ref->Data(), ref->GetSize());

	PacketHeader* head = w.Reserve<PacketHeader>();
	w << (uint16)data.id << (uint8)data.level << (uint8)data.nameSize;
	w.Write((void*)data.name.data(), data.nameSize);

	head->size = w.WriteSize();
	head->type = type;
	ref->Close(w.WriteSize());

	return ref;
}
