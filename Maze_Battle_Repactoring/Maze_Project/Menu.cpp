#include "pch.h"
#include "Menu.h"
#include "NetworkManager.h"

#include <QtCore/qdebug.h>
#include <string>

void Menu::Init()
{
	_view = new QGraphicsView();

	Loby_Init();
	Menu_Init();
}

void Menu::Start()
{
	Show_Menu();

	_view->show();
}

void Menu::Clear()
{
	xdelete(_view);
}

void Menu::Set_Loby()
{
	Windows_setting(300, 450);
	_view->setScene(&Loby);
}
void Menu::Set_Room()
{
	Windows_setting(250, 250);
	_view->setScene(&Room);
}
void Menu::Set_Menu()
{
	Windows_setting(250, 250);
	_view->setScene(&Menus);
}

void Menu::Windows_setting(int width, int height)
{
	_view->setMinimumHeight(height);
	_view->setMinimumWidth(width);

	_view->setMaximumHeight(height);
	_view->setMaximumWidth(width);
}
void Menu::Menu_Init()
{
	Menus.addWidget(&_Create_Button);
	Menus.addWidget(&_In_Button);

	Menus.addWidget(&_Level_INPUT);
	Menus.addWidget(&_NAME_INPUT);

	Menus.addWidget(&_Level_LABEL);
	Menus.addWidget(&_NAME_LABEL);

	Room.addWidget(&_button);
	Room.addWidget(&_button2);

	Room.addWidget(&_Host_Information);
	Room.addWidget(&_Client_Information);

	_Level_INPUT.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 100, 100, 20);
	_NAME_INPUT.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 100, 100, 20);

	_Level_LABEL.setText("Level (2~5)");
	_NAME_LABEL.setText("Room Name Input");

	_Level_LABEL.setAlignment(Qt::AlignCenter);
	_NAME_LABEL.setAlignment(Qt::AlignCenter);

	_Level_LABEL.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 120, 100, 20);
	_NAME_LABEL.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 120, 100, 20);

	_Host_Information.setAlignment(Qt::AlignCenter);
	_Client_Information.setAlignment(Qt::AlignCenter);

	_Host_Information.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 120, 100, 20);
	_Client_Information.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 120, 100, 20);
	
	_Create_Button.setText("Create Room");
	_In_Button.setText("Inside Room");

	_Create_Button.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 50, 100, 20);
	_In_Button.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 50, 100, 20);

	_button.setText("Start Game");
	_button2.setText("Exit");

	_button.setGeometry(_view->minimumWidth() / 2 - 120, _view->minimumHeight() / 2 - 50, 100, 20);
	_button2.setGeometry(_view->minimumWidth() / 2 + 20, _view->minimumHeight() / 2 - 50, 100, 20);
	
	Connect = QGraphicsScene::connect(&_button2, SIGNAL(clicked()), this, SLOT(Show_Menu()));
	QGraphicsScene::connect(&_Create_Button, SIGNAL(clicked()), this, SLOT(Create_Room()));

	QGraphicsScene::connect(&_In_Button, SIGNAL(clicked()), this, SLOT(Loby_Sho()));
	QGraphicsScene::connect(&_button, SIGNAL(clicked()), this, SLOT(Start_Game()));
}

void Menu::Loby_Init()
{
	_Loby_Button = new QButtonGroup(this);

	for (int i = 0; i < 10; i++) {
		_Loby_Label[i] = new QLabel;
		_Loby_Label[i]->setGeometry(10, (i * 35), 180, 25);

		_Input_Button[i] = new QPushButton;
		_Input_Button[i]->setGeometry(210, (i * 35), 40, 25);
		_Input_Button[i]->setText(QString::fromLocal8Bit("입장"));
		_Input_Button[i]->hide();

		_Loby_Button->addButton(_Input_Button[i], i);

		Loby.addWidget(_Loby_Label[i]);
		Loby.addWidget(_Input_Button[i]);
	}
	Loby.addWidget(&_Reset_Button);

	_Reset_Button.setText("Reset");
	_Reset_Button.setGeometry(10, 350, 50, 25);
	QGraphicsScene::connect(&_Reset_Button, SIGNAL(clicked()), this, SLOT(Recv_Data()));
	QGraphicsScene::connect(_Loby_Button, SIGNAL(buttonClicked(int)), this, SLOT(InSide_Room(int)));
}

//void Menu::Start_Game()
//{
//	int _size = Networking::user.loby.Level;
//	int _trap = _size * 5;
//	_size *= 10;
//	_size += 1;
//
//	Networking::user.loby.GameStart = true;
//
//	if (Networking::user.loby.Type == 1) {
//		send(Networking::user.socket, reinterpret_cast<char*>(&Networking::user.loby), sizeof(Networking::user.loby), 0);
//	}
//	if (Networking::user.loby.Enemy) {
//		board = new Board(_size, _trap);
//
//		Windows_setting(_size * (Consts::BOARD_IMAGE_SIZE + 1), _size * (Consts::BOARD_IMAGE_SIZE + 1) + 30);
//		_view->setScene(board);
//		_view->setAlignment(Qt::AlignTop);
//		_view->update();
//	}
//}
//
//void Menu::InSide_Room(int i)
//{
//	disconnect(Connect);
//
//	Connect = QGraphicsScene::connect(&_button2, SIGNAL(clicked()), this, SLOT(Loby_Show()));
//	Connect = QGraphicsScene::connect(this, SIGNAL(start()), this, SLOT(Start_Game()));
//
//	Networking::SetData(2, i, 2, Networking::user.loby.name);
//	int retVal = send(Networking::user.socket, reinterpret_cast<char*>(&Networking::user.loby), sizeof(Networking::user.loby), 0);
//
//	if (retVal == SOCKET_ERROR)
//		Networking::err_quit("Loby Send");
//	retVal = recv(Networking::user.socket, reinterpret_cast<char*>(&Networking::user.loby), retVal, 0);
//
//	if (retVal == SOCKET_ERROR)
//		Networking::err_quit("Loby Recv");
//
//	if (Networking::user.loby.RoomNumber == -1) {
//		Loby_Show();
//	}
//	else {
//		_Host_Information.setText(Networking::user.loby.name.c_str());
//		_button.hide();
//
//		Create_Thread();
//		Set_Room();
//	}
//}
//
//
////방 로비 입장
//void Menu::Loby_Show()
//{	
//	int _check = _Level_INPUT.text().toInt();
//	if (_check > 1 && _check < 6) {
//		if (isLoop == true) {
//			tmp.Type = -1;
//			::send(Networking::user.socket, reinterpret_cast<char*>(&tmp), sizeof(tmp), 0);
//
//			isLoop = false;
//		}
//		else {
//			Socket_init();
//
//			if (::connect(Networking::user.socket, reinterpret_cast<SOCKADDR*>(&Networking::user.sockaddr), sizeof(SOCKADDR_IN))) {
//				Networking::err_quit("Connect");
//				return;
//			}
//		}
//		string name = _NAME_INPUT.text().toStdString();
//		int Level = _Level_INPUT.text().toInt();
//		Networking::SetData(2, -1, Level, name);
//
//		Recv_Data();
//		Set_Loby();
//	}
//}

////방 생성
//void Menu::Create_Room() 
//{
//	int _check = _Level_INPUT.text().toInt();
//	if (_check > 1 && _check < 6) {
//		string name = _NAME_INPUT.text().toStdString();
//		int Level = _Level_INPUT.text().toInt();
//		Networking::SetData(1, 1, Level, name);
//
//		int retVal = ::send(Networking::user.socket, reinterpret_cast<char*>(&Networking::user.loby), sizeof(Networking::user.loby), 0);
//		if (retVal == SOCKET_ERROR)
//			Networking::err_quit("Send");
//		int number;
//		retVal = ::recv(Networking::user.socket, reinterpret_cast<char*>(&number), sizeof(int), 0);
//		Networking::user.loby.RoomNumber = number;
//		_Host_Information.setText(Networking::user.loby.name.c_str());
//		Create_Thread();
//		Set_Room();
//	}
//}
void Menu::Show_Menu()
{
	Set_Menu();
}