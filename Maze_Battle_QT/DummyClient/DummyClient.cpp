#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
#include "pch.h"
#include <iostream>
#include "resource.h"

#include <winsock2.h>
#include <thread>
#include <mswsock.h>
#include <ws2tcpip.h>

#define PORT	9000
#define SERVERIP "127.0.0.1"
#define BUFSIZE 512

//윈도우 프로시저
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
//편집 함수
void DisplayText(const char* fmt, ...);
//오류 출력 함수
void err_quit(const char* msg);

char buf[BUFSIZE + 1];
int check;
HWND hCreateRoom, hInRoom;
HWND hEdit1;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)&DlgProc);

	WSACleanup();
	return 0;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParm, LPARAM lParm) {
	switch (uMsg) {
	case WM_INITDIALOG:
		hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
		hCreateRoom = GetDlgItem(hDlg, CREATE_ROOM);
		hInRoom = GetDlgItem(hDlg, IN_ROOM);
		SendMessage(hEdit1, EM_SETLIMITTEXT, BUFSIZE, 0);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParm)) {
		case CREATE_ROOM:
			EnableWindow(hCreateRoom, FALSE);
			EnableWindow(hInRoom, FALSE);
			//WaitForSingleObject(hReadEvent, INFINITE);
			check = 1;
			GetDlgItemText(hDlg, IDC_EDIT1, (LPWSTR)buf, BUFSIZE + 1);
			//SetEvent(hWriteEvent);
			SetFocus(hEdit1);
			SendMessage(hEdit1, EM_SETSEL, 0, -1);
			return TRUE;
		case IN_ROOM:
			EnableWindow(hCreateRoom, FALSE);
			EnableWindow(hInRoom, FALSE);
			//WaitForSingleObject(hIPButton, INFINITE);
			check = 0;
			GetDlgItemText(hDlg, IDC_EDIT1, (LPWSTR)buf, BUFSIZE + 1);
			//SetEvent(hWriteEvent);
			SetFocus(hEdit1);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

void DisplayText(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);

	char cbuf[256];
	vsprintf(cbuf, fmt, arg);
	int nLength = GetWindowTextLength(hEdit1);
	SendMessage(hEdit1, EM_SETSEL, nLength, nLength);
	SendMessage(hEdit1, EM_REPLACESEL, FALSE, (LPARAM)cbuf);

	va_end(arg);
}

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(PORT);

	// Connect
	while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결된 상태라면 break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			break;
		}
	}

	cout << "Connected to Server!" << endl;

	char sendBuffer[100] = "Hello World";
	WSAEVENT wsaEvent = ::WSACreateEvent();
	WSAOVERLAPPED overlapped = {};
	overlapped.hEvent = wsaEvent;

	// Send
	while (true)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = sendBuffer;
		wsaBuf.len = 100;

		DWORD sendLen = 0;
		DWORD flags = 0;
		if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, flags, &overlapped, nullptr) == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSA_IO_PENDING)
			{
				// Pending
				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
				::WSAGetOverlappedResult(clientSocket, &overlapped, &sendLen, FALSE, &flags);
			}
			else
			{
				// 진짜 문제 있는 상황
				break;
			}
		}

		cout << "Send Data ! Len = " << sizeof(sendBuffer) << endl;

		this_thread::sleep_for(1s);
	}

	// 소켓 리소스 반환
	::closesocket(clientSocket);

	// 윈속 종료
	::WSACleanup();
}