#pragma once

#include "Player.h"
#include "Board.h"
#include "Consts.h"
#include "pch.h"
#include <qbuttongroup.h>

class Menu : public QGraphicsScene{
	Q_OBJECT

	SINGLETON(Menu)
private:
	void Init();
	QGraphicsView* _view;

	//게임 판
	//Board* board;

	//화면들 
	QGraphicsScene Loby;
	QGraphicsScene Menus;
	QGraphicsScene Room;
private:
	struct Loby_Data tmp;

	bool isLoop = false;
	QMetaObject::Connection Connect;
public:
	Menu(QGraphicsView* view);
	virtual ~Menu();

private:
	//초기화 부분
	void Set_Loby();
	void Set_Room();
	void Set_Menu();
	void Windows_setting(int widht, int height);
	void Menu_Init();
	void Loby_Init();

	//스레드 생성하여 주기적으로 방 리셋
	void Create_Thread();

signals:
	void start();

private slots:
	//메뉴 
	void Show_Menu();

	//로비 입장
	void Loby_Show();

	//로비에서 방 입장
	void InSide_Room(int i);

	//방 생성
	void Create_Room();

	//게임 시작
	void Start_Game();

	//로비 정보 받기
	void Recv_Data();

private:
	//게임 시작할때 정보
	QLineEdit _Level_INPUT;
	QLineEdit _NAME_INPUT;
	QLabel _Level_LABEL;
	QLabel _NAME_LABEL;

	//방 생성 후 버튼
	QPushButton _button;
	QPushButton _button2;

	//처음 화면 버튼
	QPushButton _Create_Button;
	QPushButton _In_Button;

	//로비 정보 및 입장
	QPushButton _Reset_Button;
	QLabel* _Loby_Label[10];
	QPushButton* _Input_Button[10];
	QButtonGroup* _Loby_Button;

	//방 입장한 사람들 정보
	QLabel _Host_Information;
	QLabel _Client_Information;
};