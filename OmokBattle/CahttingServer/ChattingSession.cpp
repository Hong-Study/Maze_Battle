#include "pch.h"
#include "ChattingSession.h"

ChattingSession::ChattingSession()
{
}

ChattingSession::~ChattingSession()
{
}

void ChattingSession::OnSend(const BYTE* buffer, int32 len)
{
	cout << "OnSend" << endl;
}

void ChattingSession::OnRecv(BYTE* buffer, int32 len)
{
	cout << "OnRecv " << buffer << endl;
}
