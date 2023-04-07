#pragma once
#include "PacketBuffer.h"

enum Type
{
	LOGIN = 1
	, CHAT = 2
};

struct PacketHeader
{
	uint16 size;
	Type type;
};

static char* ParsingPacket(BYTE* buffer, uint16 len)
{
	char* str = new char[len+1];
	memcpy(str, buffer + sizeof(PacketHeader), len);
	str[len] = '\0';

	return str;
}

template<typename T>
static PacketBufferRef MakePacketBuffer(T str, Type t)
{
	const uint16 dataSize = sizeof(T);
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	PacketBufferRef ref = make_shared<PacketBuffer>(packetSize);
	PacketHeader* head = reinterpret_cast<PacketHeader*>(ref->Data());
	head->size = dataSize;
	head->type = t;
	memcpy(&head[1], &str, dataSize);
	
	return ref;
}