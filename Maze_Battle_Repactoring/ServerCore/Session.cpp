#include "pch.h"
#include "Session.h"
#include "Service.h"

Session::~Session()
{
	_serviceRef = nullptr;
}

int32 Session::Send(const BYTE* buffer, int32 len)
{
	OnSend(buffer, len);
	
	while (true) {
		if (::send(_socket, reinterpret_cast<const char*>(buffer), len, 0) == SOCKET_ERROR) {
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			cout << "ERROR" << endl;
			break;
		}

		break;
	}
	
	return len;
}

int32 Session::Recv()
{
	_recvLen = recv(_socket, reinterpret_cast<char*>(_recvBuffer.WritePos()), _recvBuffer.FreeSize(), 0);
	
	if (_recvBuffer.OnWrite(_recvLen)) {
		int processLen = OnRecv(_recvBuffer.ReadPos(), _recvBuffer.DataSize());
		if (processLen < 0 || _recvBuffer.OnRead(processLen) == false)
			cout << "Read Overflow" << endl;
	}
	else
	{
		cout << "Write Overflow" << endl;
	}

	return _recvLen;
}

void Session::Disconnect()
{
	OnDisconnected();

	::SocketUtils::Close(_socket);
}
