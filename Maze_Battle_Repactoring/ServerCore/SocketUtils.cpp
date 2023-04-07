#include "pch.h"
#include "SocketUtils.h"
#include "Address.h"

bool SocketUtils::Init()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return false;

	return true;
}

SOCKET SocketUtils::CreateSocket()
{
	return socket(AF_INET, SOCK_STREAM, 0);
}

SOCKET SocketUtils::NonBlockingSet(SOCKET socket)
{	
	u_long on = 1;
	return INVALID_SOCKET == ::ioctlsocket(socket, FIONBIO, &on);
}

bool SocketUtils::Bind(SOCKET socket, Address addr)
{
	return SOCKET_ERROR == ::bind(socket, reinterpret_cast<const SOCKADDR*>(&addr.GetSockAddr()), sizeof(SOCKADDR_IN));
}

bool SocketUtils::BindAnyAddress(SOCKET socket, uint16 port)
{
	SOCKADDR_IN sockaddr;
	sockaddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = ::htons(port);

	return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&sockaddr), sizeof(SOCKADDR_IN));
}

bool SocketUtils::Listen(SOCKET socket, int32 backlog)
{
	return SOCKET_ERROR == ::listen(socket, backlog);
}

bool SocketUtils::Connect(SOCKET socket, Address addr)
{
	return SOCKET_ERROR == ::connect(socket, reinterpret_cast<const SOCKADDR*>(&addr.GetSockAddr()), sizeof(SOCKADDR_IN));
}

void SocketUtils::Close(SOCKET& socket)
{
	::closesocket(socket);
}





