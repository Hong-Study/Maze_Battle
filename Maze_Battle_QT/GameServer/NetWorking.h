#pragma once
#include "pch.h"
#include "Datas.h"
#include <NetAddress.h>

class NetWorking
{
public:
	static void Init();
	static void Clear();

	static SOCKET CreateSocket();

	static bool SetLinger(SOCKET socket, uint16 onoff, uint16 linger);
	static bool SetReuseAddress(SOCKET socket, bool flag);
	static bool SetRecvBufferSize(SOCKET socket, int32 size);
	static bool SetSendBufferSize(SOCKET socket, int32 size);
	static bool SetTcpNoDelay(SOCKET socket, bool flag);
	static bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket);

	static bool Bind(SOCKET socket, NetAddress netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backlog = SOMAXCONN);
	static void Close(SOCKET& socket);

	static bool AddScoketInfo(SOCKET sock, int Index);
	static void RemoveSocketInfo(int nIndex);
		
	static bool SetCheck(int index);
	static int WaitForMultipleEvent();
	static int NetWorkEvent(int i, WSANETWORKEVENTS& Event);

	static WSAEVENT* GetEventArray() { return _EventArray; }
	static Datas* GetSocketInfo(int index) { return _SocketInfo[index]; }
	static int GetTotalSockets() { return _totalSockets; }
	static int GetHostSockets() { return _HostSockets; }

	static void err_quit(const char* msg);
	static void err_display(int errcode);
private:
	static Datas* _SocketInfo[WSA_MAXIMUM_WAIT_EVENTS];
	static WSAEVENT _EventArray[WSA_MAXIMUM_WAIT_EVENTS];

	static int _HostSockets;
	static int _totalSockets;
};

template<typename T>
static inline bool SetSockOpt(SOCKET socket, int32 level, int32 optName, T optVal)
{
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
}