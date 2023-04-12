#pragma once

enum PKT_TYPE {
	LOGIN
	, GAME_READY
	, GAME_START
	, ROOM_CREATE
	, ROOM_INSIDE
	, ROOM_OUT
	, LOBY_INSIDE
	, PLAY_GAME
	, COUNT
};

#pragma pack(1)
struct PacketHeader
{
	uint16 size;
	PKT_TYPE type;
};

struct S_LobyInside
{
	struct LobyInfo
	{
		uint32 id;
		uint8 size;
		string name;
	};

	uint16 offset;
	uint16 count;
};

struct C_LobyInside
{	
	uint16 id;
};

struct S_RoomCreate
{
	uint16 id;
	uint8 level;
	uint8 roomNum;
};

struct C_RoomCreate
{
	C_RoomCreate() { }
	C_RoomCreate(uint16 id, uint8 level, string name)
		: id(id), level(level), name(name), nameSize(name.length()) {}

	uint16 id;
	uint8 level;
	uint8 nameSize;
	string name;
};

struct S_RoomInside
{
	uint16 id;
	uint16 hostId;
	uint8 level;
	uint8 roomNum;
};

struct C_RoomInside
{
	uint16 id;
	uint8 roomNum;
};
#pragma pack()

