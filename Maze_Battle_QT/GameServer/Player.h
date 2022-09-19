#pragma once
#include "pch.h"

enum class PlayerState {
	LOGIN,
	HOST_READY,
	HOST_START,
	LOBY_OUT,
	LOBY_INSIDE,
	CLIENT_READY,
	CLIENT_START,
	PLAY_GAME,
};

#pragma pack(1)
struct PKT_H {
	uint16 packetSize;
	uint16 id;
	PlayerState pt;
};

struct PKT_S {
	uint16 mapSize;
	std::string name;
};

struct PKT_C{
	uint16 roomNum;
	std::string name;
};

struct LOBY {
	std::string name;
};
#pragma pack()

//로비 부분
struct Loby_Data {
	PlayerState Type;
	uint16 Level;
	uint16 RoomNumber;
	bool GameStart;
	bool Win;
	std::string name;
};