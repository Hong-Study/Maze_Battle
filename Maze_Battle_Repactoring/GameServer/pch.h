#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "Lib\\ServerCore\\Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Lib\\ServerCore\\Release\\ServerCore.lib")
#endif

#include <pch.h>

#include "Consts.h"
#include "Macro.h"

#include<stdio.h>
#include<stdlib.h>
#include<thread>