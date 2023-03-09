#pragma once
#include <Session.h>

class DummySession : public Session
{
public:
	DummySession();
	~DummySession();

	virtual void OnSend(const BYTE* buffer, int32 len) override;
	virtual void OnRecv(BYTE* buffer, int32 len) override;
};
