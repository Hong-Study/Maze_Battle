#include "pch.h"

enum class TileType {
	Wall,
	Empty,
	USER,
	Trap,
	Win
};
enum class TileVisible {
	Visible, // 시야 내 구간
	Invisible, // 시야 외 구간
	detectInvisible, // 시야 내 구간 -> 외 구간 바뀜
	alreadyVisible // 시야 내 구간 -> 외 구간으로 이미 바뀐 구간
};
enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	skill1
};

//로비 부분
struct Loby_Data {
	int Type;
	int Level;
	int RoomNumber;
	bool GameStart;
	bool Win;
	bool Enemy = false;
	std::string name;
};