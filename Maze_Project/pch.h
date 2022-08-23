#pragma once

#include <iostream>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Types.h"
//#include "Networking.h"
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