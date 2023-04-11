#pragma once
#include "pch.h"
class MapInfo
{
private:
	struct Node {
		TileType type;
		TileVisible vision;
		bool came;
	};	
	int32 _size;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int32 _trap;

public:
	MapInfo(int32 n);
	~MapInfo();

	int32 GetSize() { return _size; }
	vector<vector<Node>>& GetBoard() { return _board; }
	vector<Node>& GetBoardIndex(int32 index) { return _board[index]; }

private:
	// 초기화 함수들
	void GetnarateByBinaryTree();
	void RecursiveBackTracking(int y, int x);
	void Setting_Lighting(int y, int x, bool m);
	void Make_Trap();
	int check(int y, int x);
	void shuffleArray(int* array, int size);
	int inRange(int y, int x);
	int rand(int a, int b);

	vector<vector<Node>> _board;		// 미니맵
};