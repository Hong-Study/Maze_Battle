#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Lib\\Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Lib\\Release\\ServerCore.lib")
#endif

#include <pch.h>