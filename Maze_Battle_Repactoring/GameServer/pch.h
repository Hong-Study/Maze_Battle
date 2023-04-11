#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef _DEBUG
#pragma comment(lib, "Lib\\Debug\\ServerCore.lib")
#else
#pragma comment(lib, "Lib\\Release\\ServerCore.lib")
#endif

#include "CorePch.h"
#include "Consts.h"
#include "Macro.h"

#include<stdio.h>
#include<stdlib.h>
#include<thread>