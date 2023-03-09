#include "pch.h"
#include "Session.h"

Session::~Session()
{
	_serviceRef = nullptr;
	SocketUtils::Close(_socket);
}

void Session::Dispatch(WSANETWORKEVENTS networkEvent)
{
	if (networkEvent.lNetworkEvents & FD_READ)
		Recv();
}

int32 Session::Send(const BYTE* buffer, int32 len)
{
	if (_recvLen)
		OnSend(buffer, len);
	return ::send(_socket, reinterpret_cast<const char*>(&buffer), len, 0);
}

int32 Session::Recv()
{
	ZeroMemory(&_recvBuffer, RECVSIZE);
	_recvLen = recv(_socket, reinterpret_cast<char*>(&_recvBuffer), RECVSIZE, 0);
	
	OnRecv(_recvBuffer, _recvLen);

	return _recvLen;
}
