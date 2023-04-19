#pragma once
#include "ServerSession.h"
#include "Service.h"

struct ServerDesc
{
    wstring appName = L"GameServer";
    HINSTANCE hInstance = 0;
    HWND hWnd = 0;
    HWND phWnd = 0;
    int32 cmdShow = 0;
    float width = 800;
    float height = 600;
    bool vsync = false;
    bool windowed = true;
};

class WindowsCreater
{
    SINGLETON(WindowsCreater)
public:
    void Init();
    bool Run(HINSTANCE hInstance, int32 nCmdShow);
    bool Run(ServerDesc& desc);
    ServerDesc GetDesc() { return _desc; }

private:
    bool Start();
    ATOM MyRegisterClass();
    BOOL InitInstance();
    ServerServiceRef GetService() { return _service; }
    static LRESULT CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
    ServerDesc _desc;
    ServerServiceRef _service;
};