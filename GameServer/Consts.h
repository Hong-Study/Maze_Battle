#include "pch.h"

enum class TileType {
	Wall,
	Empty,
	USER,
	Trap,
	Win
};
enum class TileVisible {
	Visible, // �þ� �� ����
	Invisible, // �þ� �� ����
	detectInvisible, // �þ� �� ���� -> �� ���� �ٲ�
	alreadyVisible // �þ� �� ���� -> �� �������� �̹� �ٲ� ����
};
enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	skill1
};

//�κ� �κ�
struct Loby_Data {
	int Type;
	int Level;
	int RoomNumber;
	bool GameStart;
	bool Win;
	bool Enemy = false;
	std::string name;
};