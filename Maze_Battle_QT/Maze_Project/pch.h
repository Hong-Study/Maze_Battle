#pragma once

#include <iostream>
using namespace std;

#include <winsock2.h>
//#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Types.h"
#include "Consts.h"

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <thread>

#include <QtWidgets/qgraphicsScene>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/qpushbutton.h>
#include <QTWidgets/qgraphicsview.h>
#include <QTWidgets/qlineedit.h>
#include <QTWidgets/qlabel.h>

#define BUFSIZE 512
#define PORT 9000
#define SERVERIP "127.0.0.1"

//#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}

#ifdef _DEBUG
#pragma comment(lib, "Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Release\\ServerCore.lib")
#endif