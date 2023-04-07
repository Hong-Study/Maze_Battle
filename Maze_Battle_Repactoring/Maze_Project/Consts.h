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

struct Loby_Data {
    int Type;
    int Level;
    int RoomNumber;
    bool GameStart = false;
    bool Win;
    bool Enemy = false;
    std::string name;
};