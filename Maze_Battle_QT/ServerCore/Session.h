#pragma once

#include "NetAddress.h"

class Session : public enable_shared_from_this<Session>
{
public:
	Session();
	virtual ~Session();

public:
	void		SetAddress(NetAddress address) { _netAddress = address; }
	NetAddress	GetAddress() { return _netAddress; }
	SOCKET		GetSocket() { return _socket; }

public:
	//�������̽� ����
	virtual HANDLE	GetHandle();
	virtual void	Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes) override;

public:
	char _recvBuffer[1000];

private:
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};
	Atomic<bool> _connected = false;
};