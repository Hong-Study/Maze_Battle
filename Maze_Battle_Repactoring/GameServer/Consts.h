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