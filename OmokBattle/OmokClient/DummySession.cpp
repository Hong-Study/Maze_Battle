#include "pch.h"
#include "DummySession.h"

DummySession::DummySession()
{

		string str = "Hello World";

		if (Send(reinterpret_cast<const BYTE*>(str.c_str()), str.length()) == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK)
}

DummySession::~DummySession()
{

}

void DummySession::OnSend(const BYTE* buffer, int32 len)
{
	cout << "OnSend " << len << endl;
}

void DummySession::OnRecv(BYTE* buffer, int32 len)
{
	cout << "OnRecv " << buffer << endl;
}
