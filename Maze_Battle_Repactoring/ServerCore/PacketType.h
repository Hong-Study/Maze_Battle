#pragma once

enum class PKT_TYPE {
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
	uint16 id;
	uint8 level;
};

struct S_RoomInside
{
	uint16 id;
	uint16 hostId;
	
};

struct C_RoomInside
{
	uint16 id;
	uint8 roomNum;

};

struct userInfo
{
	uint16 id;
};
struct RoomInfo
{
	uint8 roomNum;
};
#pragma pack()

