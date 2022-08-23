#include "pch.h"
#include "Networking.h"
#include <qdebug.h>

/*----------------
	Networking
-----------------*/

User_Data Networking::user;

void Networking::Init()
{
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 2), & wsaData);
}

void Networking::Clear()
{
	::WSACleanup();
}

SOCKET Networking::CreateSocket()
{
	return ::socket(AF_INET, SOCK_STREAM, 0);
}

bool Networking::SetLinger(SOCKET& _socket, uint16 onoff, uint16 linger)
{
	LINGER option;
	option.l_onoff = onoff;
	option.l_linger = linger;
	return SetSockOpt(_socket, SOL_SOCKET, SO_LINGER, option);
}

bool Networking::SetReuseAddress(SOCKET& _socket, bool flag)
{
	return SetSockOpt(_socket, SOL_SOCKET, SO_REUSEADDR, flag);
}

bool Networking::SetRecvBufferSize(SOCKET& _socket, int32 size)
{
	return SetSockOpt(_socket, SOL_SOCKET, SO_RCVBUF, size);
}

bool Networking::SetSendBufferSize(SOCKET& _socket, int32 size)
{
	return SetSockOpt(_socket, SOL_SOCKET, SO_SNDBUF, size);
}

bool Networking::SetTcpNoDelay(SOCKET& _socket, bool flag)
{
	return SetSockOpt(_socket, SOL_SOCKET, TCP_NODELAY, flag);
}

void Networking::Close()
{
	if (user.socket != INVALID_SOCKET)
		::closesocket(user.socket);
	user.socket = INVALID_SOCKET;
}

//int Networking::Send_Loby(SOCKET& _socket, Loby_Data& loby)
//{
//	return send(_socket, reinterpret_cast<char*>(&loby), sizeof(loby), 0);
//}
//
//int Networking::Send_Game(SOCKET& _socket, Loby_Data& game)
//{
//	return send(_socket, reinterpret_cast<char*>(&game), sizeof(game), 0);
//}
//
//int Networking::Recv_Loby(SOCKET& _socket, Loby_Data& loby)
//{
//	return recv(_socket, reinterpret_cast<char*>(&loby), sizeof(BUFSIZE), 0);
//}
//
//int Networking::Recv_Game(SOCKET& _socket, Loby_Data& game)
//{
//	return recv(_socket, reinterpret_cast<char*>(&game), sizeof(BUFSIZE), 0);
//}

void Networking::SetData(int _type, int _RoomNumber, int _level, std::string _name)
{
	user.loby.Type = _type;
	user.loby.RoomNumber = _RoomNumber;
	user.loby.Level = _level;
	user.loby.name = _name;
}

void Networking::err_quit(const char* msg) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	qDebug() << msg << " " << (const char*)lpMsgBuf;;
	LocalFree(lpMsgBuf);
}

void Networking::err_display(int errcode) {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	qDebug() << (const char*)lpMsgBuf;;
	LocalFree(lpMsgBuf);
}