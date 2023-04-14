#include "pch.h"
#include "ServerPacketHandler.h"

bool ServerPacketHandler::HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref)
{
	BufferReader read(buffer, len);
	C_RoomCreate room;
	read >> room.id >> room.level >> room.nameSize;
	room.name.resize(room.nameSize);
	read.Read((void*)room.name.data(), room.nameSize);

	cout << room.name << endl;

	return true;
}

bool ServerPacketHandler::HandlerLogin(BYTE* buffer, uint32 len, SessionRef ref)
{
	return true;
}
