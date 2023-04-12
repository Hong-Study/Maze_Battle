#pragma once

#include "Player.h"
#include "Board.h"
#include "Consts.h"
#include <qbuttongroup.h>

class Menu : public QGraphicsScene{
	Q_OBJECT

	SINGLETON(Menu)

private:
	void Init();

	//�ʱ�ȭ �κ�
	void Set_Loby();
	void Set_Room();
	void Set_Menu();
	void Windows_setting(int widht, int height);
	void Menu_Init();
	void Loby_Init();

	//������ �����Ͽ� �ֱ������� �� ����
	//void Create_Thread();

public:
	void Start();
	void Clear();

signals:
	void start();

private slots:
	//�޴� 
	void Show_Menu();
	//�κ� ����
	//void Loby_Show();
	////�κ񿡼� �� ����
	//void InSide_Room(int i);
	////�� ����
	//void Create_Room();
	////���� ����
	//void Start_Game();

//public:
//	void Show_Room();
	
private:
	QGraphicsView* _view;

	//���� ��
	//Board* board;

	//ȭ��� 
	QGraphicsScene Loby;
	QGraphicsScene Menus;
	QGraphicsScene Room;

	bool isLoop = false;
	QMetaObject::Connection Connect;

private:
	//���� �����Ҷ� ����
	QLineEdit _Level_INPUT;
	QLineEdit _NAME_INPUT;
	QLabel _Level_LABEL;
	QLabel _NAME_LABEL;

	//�� ���� �� ��ư
	QPushButton _button;
	QPushButton _button2;

	//ó�� ȭ�� ��ư
	QPushButton _Create_Button;
	QPushButton _In_Button;

	//�κ� ���� �� ����
	QPushButton _Reset_Button;
	QLabel* _Loby_Label[10];
	QPushButton* _Input_Button[10];
	QButtonGroup* _Loby_Button;

	//�� ������ ����� ����
	QLabel _Host_Information;
	QLabel _Client_Information;

};