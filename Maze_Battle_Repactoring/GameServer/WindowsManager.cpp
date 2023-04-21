#include "pch.h"
#include "WindowsManager.h"
#include "ServerSession.h"
#include "Service.h"
#include "PacketHandler.h"

function<SessionRef(void)> Serverfactory = make_shared<ServerSession>;

void WindowsManager::Init()
{
    SocketUtils::Init();

    _service = make_shared<ServerService>(Address(L"127.0.0.1", 5000), Serverfactory, 10);
    _service->Listen();

    _desc.appName = L"GameServer";
    _desc.vsync = false;
    _desc.width = 800;
    _desc.height = 600;
}

bool WindowsManager::Run(HINSTANCE hInstance, int32 nCmdShow)
{
    _desc.hInstance = hInstance;
    _desc.cmdShow = nCmdShow;
    return Start();
}

bool WindowsManager::Run(ServerDesc& desc)
{
    _desc = desc;
    return Start();
}

bool WindowsManager::Start()
{
    MyRegisterClass();

    if (!InitInstance())
        return false;

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM WindowsManager::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DlgProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _desc.hInstance;
    wcex.hIcon = LoadIcon(_desc.hInstance, MAKEINTRESOURCE(IDD_DIALOG1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = _desc.appName.c_str();
    wcex.hIconSm = wcex.hIcon;

    return RegisterClassExW(&wcex);
}

BOOL WindowsManager::InitInstance()
{
    RECT windowRect = { 0, 0, _desc.width, _desc.height };

    ::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

    _desc.hWnd = CreateWindowW(_desc.appName.c_str(), _desc.appName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, _desc.hInstance, nullptr);

    _desc.hWnd = CreateDialog(WINDOW->GetDesc().hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _desc.phWnd, DlgProc);

    if (!_desc.hWnd)
        return FALSE;

    ::ShowWindow(_desc.hWnd, _desc.cmdShow);
    //::UpdateWindow(_desc.hWnd);

    return true;
}

LRESULT CALLBACK WindowsManager::DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage) {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            WSACleanup();
            PostQuitMessage(0);
            return TRUE;
        case IDC_START:
            SERVICE->Start();
            return TRUE;

        case IDC_CLOSE:
            SERVICE->Close();
            return TRUE;
        default:
            return TRUE;
        }
        return TRUE;
    }

    return FALSE;
}