#include "pch.h"
#include "NetWorking.h"

/*----------------
	NetWorking
-----------------*/
int NetWorking::_HostSockets = 0;
int NetWorking::_totalSockets = 0;
Datas* NetWorking::_SocketInfo[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT NetWorking::_EventArray[WSA_MAXIMUM_WAIT_EVENTS];

void NetWorking::Init()
{
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 2), &wsaData);

	fill_n(_SocketInfo, WSA_MAXIMUM_WAIT_EVENTS,  nullptr);
	fill_n(_EventArray, WSA_MAXIMUM_WAIT_EVENTS, nullptr);
}

void NetWorking::Clear()
{
	::WSACleanup();
}

SOCKET NetWorking::CreateSocket()
{
	return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

bool NetWorking::SetLinger(SOCKET socket, uint16 onoff, uint16 linger)
{
	LINGER option;
	option.l_onoff = onoff;
	option.l_linger = linger;
	return SetSockOpt(socket, SOL_SOCKET, SO_LINGER, option);
}

bool NetWorking::SetReuseAddress(SOCKET socket, bool flag)
{
	return SetSockOpt(socket, SOL_SOCKET, SO_REUSEADDR, flag);
}

bool NetWorking::SetRecvBufferSize(SOCKET socket, int32 size)
{
	return SetSockOpt(socket, SOL_SOCKET, SO_RCVBUF, size);
}

bool NetWorking::SetSendBufferSize(SOCKET socket, int32 size)
{
	return SetSockOpt(socket, SOL_SOCKET, SO_SNDBUF, size);
}

bool NetWorking::SetTcpNoDelay(SOCKET socket, bool flag)
{
	return SetSockOpt(socket, SOL_SOCKET, TCP_NODELAY, flag);
}

// ListenSocket의 특성을 ClientSocket에 그대로 적용
bool NetWorking::SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket)
{
	return SetSockOpt(socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, listenSocket);
}

bool NetWorking::Bind(SOCKET socket, NetAddress netAddr)
{
	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&netAddr.GetSockAddr()), sizeof(SOCKADDR_IN));
}

bool NetWorking::BindAnyAddress(SOCKET socket, uint16 port)
{
	SOCKADDR_IN myAddress;
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);
	myAddress.sin_port = ::htons(port);

	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&myAddress), sizeof(myAddress));
}

bool NetWorking::Listen(SOCKET socket, int32 backlog)
{
	return SOCKET_ERROR != ::listen(socket, backlog);
}

void NetWorking::Close(SOCKET& socket)
{
	if (socket != INVALID_SOCKET)
		::closesocket(socket);
	socket = INVALID_SOCKET;
}

bool NetWorking::AddScoketInfo(SOCKET sock, int Index)
{
	Datas* ptr = new Datas(sock);
	if (ptr == NULL) {
		cout << "[오류] 메모리가 부족합니다." << "\n";
		return FALSE;
	}
	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		cout << "WSACreateEvent()" << endl;
		return FALSE;
	}
	if (_totalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
		cout << "Maximum_Count" << endl;
		return FALSE;
	}
	_SocketInfo[_totalSockets] = ptr;
	_EventArray[_totalSockets] = hEvent;
	if (Index == 0) {
		if (WSAEventSelect(sock, hEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
			return false;
	}
	else {
		if (WSAEventSelect(sock, hEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
			return false;
	}

	++_totalSockets;
	return TRUE;
}

void NetWorking::RemoveSocketInfo(int nIndex)
{
	Datas* ptr = _SocketInfo[nIndex];
	_SocketInfo[nIndex] = nullptr;

	//클라 정보 얻기
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->GetSocket(), (SOCKADDR*)&clientaddr, &addrlen);

	printf("[TCP 서버] 클라이언트 종료 : IP  주소 = %s, 포트번호 = %d\r\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	closesocket(ptr->GetSocket());

	delete ptr;

	/*WSACloseEvent(_EventArray[nIndex]);*/

	if (nIndex != (_totalSockets - 1)) {
		_SocketInfo[nIndex] = _SocketInfo[_totalSockets - 1];
		_EventArray[nIndex] = _EventArray[_totalSockets - 1];
	}

	--_totalSockets;
}

bool NetWorking::SetCheck(int index)
{
	int _index = (index - 1) * 2;
	if (_SocketInfo[index]->GetIndex() == 0)
		return FALSE;
	return TRUE;
}

int NetWorking::WaitForMultipleEvent()
{
	return WSAWaitForMultipleEvents(_totalSockets, _EventArray, FALSE, WSA_INFINITE, FALSE);
}

int NetWorking::NetWorkEvent(int i, WSANETWORKEVENTS& Event)
{
	return WSAEnumNetworkEvents(_SocketInfo[i]->GetSocket(), _EventArray[i], &Event);
}


void NetWorking::err_quit(const char* msg) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	cout << msg << " " << (char*)lpMsgBuf << endl;
	LocalFree(lpMsgBuf);
	//exit(1);
}

void NetWorking::err_display(int errcode) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[ 오류 ] %s\n", (char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
	//exit(1);
}