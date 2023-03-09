#pragma once
#include <Session.h>

class ChattingSession : public Session
{
public:
	ChattingSession();
	~ChattingSession();

	virtual void OnSend(const BYTE* buffer, int32 len) override;
	virtual void OnRecv(BYTE* buffer, int32 len) override;
};

