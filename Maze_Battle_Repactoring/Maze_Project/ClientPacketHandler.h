#pragma once

using Func = std::function<bool(BYTE*, uint32, SessionRef)>;
extern Func func[(int)PKT_TYPE::COUNT];

class ClientPacketHandler
{
public:
	static void Init();
	static bool Dispatch(BYTE* buffer, uint32 len, SessionRef ref);

private:
	static bool HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref);

public:
	template<typename T>
	SendBufferRef MakeSendBuffer(T&& data, PKT_TYPE type);

	template<>
	SendBufferRef MakeSendBuffer(C_LobyInside&& data, PKT_TYPE type);

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
inline SendBufferRef ClientPacketHandler::MakeSendBuffer(C_LobyInside&& data, PKT_TYPE type)
{
	return SendBufferRef();
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
