#include "pch.h"
#include "WindowsCreater.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WINDOW->Run(hInstance, nShowCmd);
    
    THREAD->Join();

    return 0;
}