#include "pch.h"
#include "MapInfo.h"
#include <random>
MapInfo::MapInfo(int32 n)
{
	_size = (n * 10) + 1;
	_trap = n * 5;

	_board.resize(_size);
	for (int i = 0; i < _size; i++) {
		_board[i].resize(_size);
	}

	GetnarateByBinaryTree();
	Make_Trap();
	
	for (int y = _size - 2; y > 1; y--) {
		if (_board[y][_size - 2].type == TileType::Empty) {
			_board[y][_size - 1].type = TileType::Win;
			break;
		}
	}
}

MapInfo::~MapInfo()
{
	
}

void MapInfo::GetnarateByBinaryTree()
{
	//초기맵 설정
	for (int y = 0; y < _size; y++) {

		for (int x = 0; x < _size; x++) {
			if (x % 2 == 0 || y % 2 == 0) {
				_board[y][x].type = TileType::Wall;
			}
			else {
				_board[y][x].type = TileType::Empty;
				_board[y][x].came = false;
			}
			_board[y][x].vision = TileVisible::Invisible;//모든지역 안보이게 설정
		}
	}
	RecursiveBackTracking(1, 1);
	_board[1][1].type = TileType::USER;
}

void MapInfo::RecursiveBackTracking(int y, int x)
{
	int r, nx, ny;
	int directions[5] = {
			Direction::UP,
			Direction::DOWN,
			Direction::LEFT,
			Direction::RIGHT
	};
	_board[y][x].came = true;
	shuffleArray(directions, 4);

	for (r = 0; r < 4; r++) {
		nx = x + DIR[directions[r]][0];
		ny = y + DIR[directions[r]][1];
		 
		if (inRange(ny, nx) && (_board[ny][nx].type == TileType::Empty) && !_board[ny][nx].came) {
			RecursiveBackTracking(ny, nx);
			if (ny != y) {
				_board[(ny + y) / 2][nx].type = TileType::Empty;
			}
			else {
				_board[ny][(nx + x) / 2].type = TileType::Empty;
			}
		}
	}
}
void MapInfo::Make_Trap() {
	int x, y;

	while (_trap > 0) {
		x = rand(2, _size - 2);
		y = rand(2, _size - 2);
		if (_board[y][x].type == TileType::Empty) {
			if (check(y - 1, x) == 2)
				continue;
			else if (check(y + 1, x) == 2)
				continue;
			else if (check(y, x - 1) == 2)
				continue;
			else if (check(y, x + 1) == 2)
				continue;
			else {
				_board[y][x].type = TileType::Trap;
				_trap--;
			}
		}
	}
}
int MapInfo::check(int y, int x)
{
	if (TileType::Empty == _board[y][x].type)
		return 1;
	else if (TileType::Trap == _board[y][x].type)
		return 2;
	else
		return 0;
}
int MapInfo::inRange(int y, int x)
{
	return (y > 0 && y < _size - 1) && (x > 0 && x < _size - 1);
}

int MapInfo::rand(int a, int b)
{
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(a, b);

	return dis(gen);
}
void MapInfo::Setting_Lighting(int y, int x, bool m)
{
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (_board[i][j].vision == TileVisible::Visible)
				_board[i][j].vision = TileVisible::detectInvisible;
		}
	}
}

void MapInfo::shuffleArray(int* array, int size)
{
	int i, r, temp;
	for (i = 0; i < (size - 1); ++i)
	{
		r = i + (rand(0, 4) % (size - i));
		temp = array[i];
		array[i] = array[r];
		array[r] = temp;
	}
}

