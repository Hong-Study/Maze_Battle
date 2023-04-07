#include "pch.h"
#include "ServerSession.h"

ServerSession::ServerSession()
{

}

ServerSession::~ServerSession()
{

}

void ServerSession::OnConnected()
{
	string str = "Hello World";
	cout << Send(reinterpret_cast<const BYTE*>(str.c_str()), str.length()) << endl;
}

void ServerSession::OnDisconnected()
{
}

int32 ServerSession::OnSend(const BYTE* buffer, int32 len)
{
	const char* str = reinterpret_cast<const char*>(buffer);
	cout << "OnSend : " << str << " / " << len << endl;
}

int32 ServerSession::OnRecv(BYTE* buffer, int32 len)
{
    cout << "Recv : " << len << endl;

    //게임 시작
    
}
