#pragma once
#include "pch.h"

namespace Consts {
    const std::string paths[]{
        "Resouce\\Wall.png",
        "Resouce\\Empty.png",
        "Resouce\\User.png",
        "Resouce\\Black.png",
        "Resouce\\InvisibleEmpty.png",
        "Resouce\\Trap.png"

    };
    const int BOARD_IMAGE_SIZE = 20;
};

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

struct Loby_Data {
    int Type;
    int Level;
    int RoomNumber;
    bool GameStart = false;
    bool Win;
    bool Enemy = false;
    std::string name;
};