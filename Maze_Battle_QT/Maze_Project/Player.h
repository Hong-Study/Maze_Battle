#pragma once
#include<conio.h>
#include<iostream>
#include <QtCore/qstring.h>

class Player {
private:
	int _x;
	int _y;
	int _Check_Trap;
	int _show_map;

public:
	Player(int x, int y, int size)
		: _x(x)
		, _y(y)
		, _Check_Trap(size / 2)
		, _show_map(size) {}

	int X() const {
		return _x;
	}
	int Y() const{
		return _y;
	}
	void set_X(int x){
		_x = x;
	}
	void set_Y(int y){
		_y = y;
	}
	int left_Check() {
		if (_Check_Trap <= 0)
			return 0;
		return _Check_Trap;
	}
	int left_show() {
		if (_show_map <= 0)
			return 0;
		return _show_map;
	}
	bool Check() {
		if (_Check_Trap-- <= 0)
			return false;
		return true;
	}
	bool Show_Mape() {
		if (_show_map-- <= 0) {
			if (_show_map < 0)
				_show_map = 0;
			return false;
		}
		return true;
	}
};