#pragma once
#include "pch.h"

class Networking
{
public:
	static void Init();
	static void Clear();

	static SOCKET CreateSocket();

	static bool SetLinger(SOCKET& _socket, uint16 onoff, uint16 linger);
	static bool SetReuseAddress(SOCKET& _socket, bool flag);
	static bool SetRecvBufferSize(SOCKET& _socket, int32 size);
	static bool SetSendBufferSize(SOCKET& _socket, int32 size);
	static bool SetTcpNoDelay(SOCKET& _socket, bool flag);

	static void Close();

	/*static int Send_Loby(SOCKET& _socket, Loby_Data& loby);
	static int Send_Game(SOCKET& _socket, Loby_Data& game);

	static int Recv_Loby(SOCKET& _socket, Loby_Data& loby);
	static int Recv_Game(SOCKET& _socket, Loby_Data& game);*/

	static void err_quit(const char* msg);
	static void err_display(int errcode);

	static void SetData(int _type, int _RoomNumber, int _level, std::string _name);

public:
	static User_Data user;
};

template<typename T>
static inline bool SetSockOpt(SOCKET socket, int32 level, int32 optName, T optVal)
{
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
}