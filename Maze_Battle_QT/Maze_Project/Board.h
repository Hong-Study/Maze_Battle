#include <QtWidgets/qgraphicsScene>
//#include <QtWidgets/QgraphicsRectItem>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qgraphicseffect.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlabel.h>
#include <QtCore/qstring.h>

#include <iostream>

#include "item.h"
#include "Player.h"
#include "Music.h"

class Board : public QGraphicsScene {
	Q_OBJECT
private:
	struct Node {
		TileType type;
		TileVisible vision;
		bool came;
	};

	Node** _board;		// �̴ϸ�
	std::vector<std::vector<Item*>> _items;		//������ ����
	QGraphicsRectItem _root;
	Player* _player;
	const int DIR[4][2] = { {0,-2},{0,+2},{-2,0},{+2,0} };
	int _size;
	int _trap;
	bool win_Check = false;
	QPushButton victory;
	QPushButton Lose;

	QLabel UI;
	QString UI_Text;
	//Music music;

private slots:
	void Win_Click();
	void Lose_Click();

public:
	Board::Board(int size, int trap);
	virtual Board::~Board();

private:
	void Board::removeItem(int row, int colum);		//������ ����
	void Board::addItem(int row, int colum);		//������ �߰�

	void Board::moveCharcter(int y0, int x0, int y1, int x1);	//ĳ���� �̵�
	void Board::moveItem(Item* item, int toRow, int toColum);	//�����

	int Board::check(int y, int x);				//���� ���� �������� �Ǵ�
	void Board::keyPressEvent(QKeyEvent* event);
	
	int rand(int a, int b);		//a~b ���� ���� �μ� ����
	void Setting_Lighting(int y, int x, bool m);
	void usingItem1(int y, int x);
	void new_Setting(int y, int x, bool m);
};