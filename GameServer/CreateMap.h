#pragma once
#include "pch.h"
class CreateMap
{
private:
	struct Node {
		TileType type;
		TileVisible vision;
		bool came;
	};	
	int _size;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _trap;
public:
	Node** _board;		// ¹Ì´Ï¸Ê

public:
	CreateMap(int n);
	virtual ~CreateMap();

	int GetSize() { return _size; }

private:
	void GetnarateByBinaryTree();
	void RecursiveBackTracking(int y, int x);
	void Setting_Lighting(int y, int x, bool m);
	void Make_Trap();
	int check(int y, int x);
	void shuffleArray(int* array, int size);
	int inRange(int y, int x);
	int rand(int a, int b);
};