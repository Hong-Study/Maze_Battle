#pragma once

#include <string>
#include <QtWidgets/QgraphicsPixmapItem>
#include "Consts.h"

class Item : public QGraphicsPixmapItem {
public:
	Item(const std::string& path, int row, int colum, QGraphicsItem* parent) 
		: QGraphicsPixmapItem(QPixmap(path.c_str()).scaled(Consts::BOARD_IMAGE_SIZE, Consts::BOARD_IMAGE_SIZE), parent)
		, _path(path), _row(row), _colum(colum) {}

	std::string path() const{		//위치 반환
		return _path;
	}
	int row() const{
		return _row;
	}
	int colum() const{
		return _colum;
	}
	void setRow(int row){
		_row = row;
	}
	void setColum(int colum){
		_colum = colum;
	}

private:
	const std::string _path;		// 사진 위치
	int _row;
	int _colum;
};