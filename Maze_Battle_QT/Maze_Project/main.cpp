#include "pch.h"
#include "Menu.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/qgraphicsScene>
//#include <fmod.hpp>
#include <array>

int main(int argc, char* argv[]){

	QApplication a(argc, argv);

	QGraphicsView view;
	Menu menu(&view);

	return a.exec();
}