#pragma once
#include "Address.h"
#include "RecvBuffer.h"

class Session : enable_shared_from_this<Session>
{
public:
	Session() : _recvBuffer(1024) {  }
	virtual ~Session();

	int32			Send(const BYTE* buffer, int32 len);
	int32			Recv();
	void			Disconnect();

	virtual void	OnConnected() abstract;
	virtual void	OnDisconnected() abstract;
	virtual int32	OnSend(const BYTE* buffer, int32 len) abstract;
	virtual int32	OnRecv(BYTE* buffer, int32 len) abstract;
	
public:
	SOCKET			GetSocket() { return _socket; }
	void			SetSocket(SOCKET socket) { _socket = socket; }
	WSAEVENT		GetEvent() { return _event; }
	void			SetEvent(WSAEVENT event) { _event = event; }
	Address&		GetAddr() { return _addr; }
	void			SetAddr(Address addr) { _addr = addr; }
	ServiceRef		GetService() { return _serviceRef; }
	void			SetService(ServiceRef ref) { _serviceRef = ref; }

private:
	SOCKET		_socket;
	WSAEVENT	_event = 0;
	Address		_addr;
	ServiceRef	_serviceRef;

	int32		_recvLen = 0;
	RecvBuffer	_recvBuffer;
};