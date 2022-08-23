#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetAddress.h"


class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();

public:
	void		SetAddress(NetAddress address) { _netAddress = address; }
	NetAddress	GetAddress() { return _netAddress; }
	SOCKET		GetSocket() { return _socket; }

public:
	//인터페이스 구현
	virtual HANDLE	GetHandle() override;
	virtual void	Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes) override;

public:
	char _recvBuffer[1000];

private:
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};
	Atomic<bool> _connected = false;
};