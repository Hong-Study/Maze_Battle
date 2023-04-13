#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib, "Lib\\ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Lib\\ServerCore\\Release\\ServerCore.lib")
#endif

#include <pch.h>

#include "Consts.h"
#include "Macro.h"
#include "NetworkManager.h"

#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <QTWidgets/qgraphicsview.h>
#include <QTWidgets/qlineedit.h>
#include <QTWidgets/qlabel.h>