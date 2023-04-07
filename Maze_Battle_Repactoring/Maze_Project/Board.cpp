#include "Board.h"
#include "pch.h"

#include <random>
#include <QtCore/qdebug.h>
#include <Qt3DInput/QKeyEvent.h>

Board::Board(int size, int trap)
	: _size(size)					//후에 사이즈 추가
	, _trap(trap)
{
	QGraphicsScene::addItem(&_root);
	//_root.setX(QGraphicsScene::sceneRect().width() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));			//X좌표 설정
	//_root.setY(QGraphicsScene::sceneRect().height() / 2 - (Consts::BOARD_IMAGE_SIZE * _size / 2));		//Y좌표 설정
	
	_board = new Node *[_size];
	for (int i = 0; i < _size; i++)
		_board[i] = new Node[_size];

	int _num = 0;
	recv(Networking::user.socket, reinterpret_cast<char*>(&_num), sizeof(int), 0);

	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			int retVal = recv(Networking::user.socket, reinterpret_cast<char*>(&_board[i][j]), _num, 0);
			if (retVal == SOCKET_ERROR) {
				exit(1);
			}
		}
	}

	_player = new Player(1, 1, _size);

	Setting_Lighting(_player->Y(), _player->X(), true);

	for (int row = 0; row < _size; ++row) {
		std::vector<Item*> rowItems(_size);
		_items.push_back(rowItems);
		for (int colum = 0; colum < _size; ++colum) {
			addItem(row, colum);
		}
	}
	victory.setText("Win!!");
	victory.setGeometry((_size*Consts::BOARD_IMAGE_SIZE) / 2 - 50, (_size * Consts::BOARD_IMAGE_SIZE) / 2 - 15, 120, 30);

	Lose.setText("Lose!!");
	Lose.setGeometry((_size * Consts::BOARD_IMAGE_SIZE) / 2 - 50, (_size * Consts::BOARD_IMAGE_SIZE) / 2 - 15, 120, 30);

	UI.setGeometry(0, _size * Consts::BOARD_IMAGE_SIZE + 10, _size * Consts::BOARD_IMAGE_SIZE, 30);
	UI.setText(UI_Text.sprintf("Delete_Trap : %d\t\t Show_Map : %d", _player->left_Check(), _player->left_show()));

	std::thread t1([=]() {
		recv(Networking::user.socket, reinterpret_cast<char*>(&win_Check), sizeof(bool), 0);
		});
	t1.detach();

	QGraphicsScene::addWidget(&Lose);
	Lose.hide();

	QGraphicsScene::addWidget(&UI);
	QGraphicsScene::connect(&victory, SIGNAL(clicked()), this, SLOT(Win_Click()));
	QGraphicsScene::connect(&Lose, SIGNAL(clicked()), this, SLOT(Lose_Click()));
}
Board::~Board()
{
	for (int row = 0; row < _items.size(); ++row) {
		for (int colum = 0; colum < _items[row].size(); ++colum) {
			removeItem(row, colum);
			delete _items[row][colum];
		}		
	}
	for (int i = 0; i < _size; i++) {
		delete _board[i];
	}
	delete _board;

	//Networking::Close();
}
void Board::Setting_Lighting(int y, int x, bool m) {
	if (m) {
		for (int i = 0; i < _size; i++) {
			for (int j = 0; j < _size; j++) {
				if (_board[i][j].vision == TileVisible::Visible)
					_board[i][j].vision = TileVisible::detectInvisible;
			}
		}
	}
	_board[y][x].vision = TileVisible::Visible;
	for (int i = 0; i < 4; i++) {
		int directX, directY;
		if (i == 0)
			directX = 1, directY = 0;
		if (i == 1)
			directX = -1, directY = 0;
		if (i == 2)
			directX = 0, directY = 1;
		if (i == 3)
			directX = 0, directY = -1;
		int a = y, b = x;
		a += directY;
		b += directX;
		_board[a + directX][b + directY].vision = TileVisible::Visible;
		_board[a - directX][b - directY].vision = TileVisible::Visible;
		_board[a][b].vision = TileVisible::Visible;
		if (check(y + directY, x + directX)) {
			while (true) {
				a += directY;
				b += directX;
				_board[a + directX][b + directY].vision = TileVisible::Visible;
				_board[a - directX][b - directY].vision = TileVisible::Visible;
				_board[a][b].vision = TileVisible::Visible;
				if (!check(a, b))
					break;
			}
		}
	}
}
void Board::removeItem(int row, int colum)
{
	auto* item = _items[row][colum];
	if (item == nullptr)
		return;

	_items[row][colum] = nullptr;
	item->setParentItem(nullptr);
	QGraphicsScene::removeItem(item);

	delete item;
}

void Board::addItem(int row, int colum)
{
	const std::string& path_wall = Consts::paths[0].c_str();
	const std::string& path_empty = Consts::paths[1].c_str();
	const std::string& path_user = Consts::paths[2].c_str();
	const std::string& path_black = Consts::paths[3].c_str();
	const std::string& path_visibleEmpty = Consts::paths[4].c_str();
	const std::string& path_trap = Consts::paths[5].c_str();

	Item* item = nullptr;
	if (_board[row][colum].vision == TileVisible::Visible) {
		if (_board[row][colum].type == TileType::Wall)
			item = new Item(path_wall, row, colum, &_root);
		else if (_board[row][colum].type == TileType::USER)
			item = new Item(path_user, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Empty || _board[row][colum].type == TileType::Win)
			item = new Item(path_empty, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Trap)
			item = new Item(path_trap, row, colum, &_root);

	}
	else if (_board[row][colum].vision == TileVisible::detectInvisible) {
		if (_board[row][colum].type == TileType::Wall)
			item = new Item(path_black, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Empty || _board[row][colum].type == TileType::Win)
			item = new Item(path_visibleEmpty, row, colum, &_root);
		else if (_board[row][colum].type == TileType::Trap)
			item = new Item(path_visibleEmpty, row, colum, &_root);
		_board[row][colum].vision = TileVisible::alreadyVisible;
	}
	else
		item = new Item(path_black, row, colum, &_root);
	
	/*if (_board[row][colum].type == TileType::Wall)
		item = new Item(path_wall, row, colum, &_root);
	else if (_board[row][colum].type == TileType::USER)
		item = new Item(path_user, row, colum, &_root);
	else
		item = new Item(path_empty, row, colum, &_root);*/

	item->setPos(colum * Consts::BOARD_IMAGE_SIZE, row * Consts::BOARD_IMAGE_SIZE +10);
	QGraphicsScene::addItem(item);					//이름이 같지만 Scene의 addItem 함수임.
	_items[row][colum] = item;
}
int Board::rand(int a, int b) {
	std::random_device rd;

	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());

	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(a, b);

	return dis(gen);
}
void Board::moveCharcter(int y0, int x0, int y1, int x1)
{
	if (win_Check)
		Lose.show();
	else if (check(y1, x1) == 3) {
		Networking::user.loby.Win = TRUE;
		send(Networking::user.socket, reinterpret_cast<char*>(&Networking::user.loby), sizeof(Networking::user.loby), 0);

		QGraphicsScene::addWidget(&victory);
	}
	else {
		if (check(y1, x1) == 2) {
			_board[y1][x1].type = TileType::Empty;
			_board[y1][x1].vision = TileVisible::detectInvisible;
			removeItem(y1, x1);
			addItem(y1, x1);

			while (true) {
				y1 = rand(2, _size - 2);
				x1 = rand(2, _size - 2);
				if (_board[y1][x1].type == TileType::Empty)
					break;
			}
		}
		_board[y1][x1].vision = TileVisible::detectInvisible;
		Item* item0 = _items[y0][x0];
		Item* item1 = _items[y1][x1];

		moveItem(item0, y1, x1);
		moveItem(item1, y0, x0);

		_items[y0][x0] = item1;
		_items[y1][x1] = item0;

		Node tmp = _board[y0][x0];
		_board[y0][x0] = _board[y1][x1];
		_board[y1][x1] = tmp;

		_player->set_X(x1);
		_player->set_Y(y1);
	}
}

void Board::moveItem(Item* item, int toRow, int toColum)
{
	item->setRow(toRow);
	item->setColum(toColum);
	item->setPos(toColum * Consts::BOARD_IMAGE_SIZE, toRow * Consts::BOARD_IMAGE_SIZE);

	_items[toRow][toColum] = item;
}

int Board::check(int y, int x) {	
	if (TileType::Empty == _board[y][x].type)
		return 1;
	else if (TileType::Trap == _board[y][x].type)
		return 2;
	else if (TileType::Win == _board[y][x].type)
		return 3;
	else
		return 0;
}

void Board::usingItem1(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int directX, directY;
		if (i == 0)
			directX = 1, directY = 0;
		if (i == 1)
			directX = -1, directY = 0;
		if (i == 2)
			directX = 0, directY = 1;
		if (i == 3)
			directX = 0, directY = -1;
		int a = y, b = x;
		if (check(a + directY, b + directX)) { //공기일때
			while (true) {
				if (!check(a + directY, b + directX)) {
					Setting_Lighting(a, b, false);
					break;
				}
				a += directY;
				b += directX;
			}
		}
	}
}

void Board::keyPressEvent(QKeyEvent* event) {
	auto x = _player->X();
	auto y = _player->Y();
	switch (event->key()) {
	case Qt::Key_Up:
		if (check(y - 1, x))
			moveCharcter(y, x, y - 1, x);
		break;
	case Qt::Key_Down:
		if (check(y + 1, x))
			moveCharcter(y, x, y + 1, x);
		break;
	case Qt::Key_Left:
		if (check(y, x - 1))
			moveCharcter(y, x, y, x - 1);
		break;
	case Qt::Key_Right:
		if (check(y, x + 1))
			moveCharcter(y, x, y, x + 1);
		break;
	case Qt::Key_A:
		if (check(y - 1, x) == 2 && _player->Check()) {
			_board[y - 1][x].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y + 1, x) == 2 && _player->Check()) {
			_board[y + 1][x].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y, x - 1) == 2 && _player->Check()) {
			_board[y][x-1].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
		else if (check(y, x + 1) == 2 && _player->Check()) {
			_board[y][x+1].type = TileType::Empty;
			removeItem(y - 1, x);
			addItem(y - 1, x);
		}
	}
	x = _player->X();
	y = _player->Y();
	if (event->key() == Qt::Key_D && _player->Show_Mape()) {
		usingItem1(y, x);
		new_Setting(y, x, false);
	}
	else
		new_Setting(y, x, true);
	UI.setText(UI_Text.sprintf("Delete_Trap : %d\t\t Show_Map : %d", _player->left_Check(), _player->left_show()));
}

void Board::new_Setting(int y, int x, bool m) {
	Setting_Lighting(y, x, m);
	for (int row = 0; row < _size; ++row) {
		for (int colum = 0; colum < _size; ++colum) {
			if (_board[row][colum].vision == TileVisible::detectInvisible) {
				removeItem(row, colum);
				addItem(row, colum);
			}
			else if (_board[row][colum].vision == TileVisible::Visible) {
				removeItem(row, colum);
				addItem(row, colum);
			}
		}
	}
}

void Board::Win_Click() {
	exit(0);
}

void Board::Lose_Click()
{
	exit(0);
}
