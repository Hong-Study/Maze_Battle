#pragma once

class Address;

class SocketUtils
{
public:
	static bool Init();
	static SOCKET CreateSocket();
	static SOCKET CreateListenSocket(SOCKET socket);

	static bool Bind(SOCKET socket, Address addr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backlog = SOMAXCONN);
	static bool Connect(SOCKET socket, Address addr);
	static void Close(SOCKET& socket);
};

