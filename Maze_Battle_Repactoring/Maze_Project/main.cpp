#include "pch.h"
#include "Menu.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>
//#include <fmod.hpp>

int main(int argc, char* argv[]){

	QApplication a(argc, argv);

	MENU->Start();

	a.exec();

	MENU->Clear();

	return 0;
}