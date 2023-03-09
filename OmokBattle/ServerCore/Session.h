#pragma once

class Address;

class Session : enable_shared_from_this<Session>
{
public:
	Session() { }
	virtual ~Session();
							
	void			Dispatch(WSANETWORKEVENTS networkEvent);

	int32			Send(const BYTE* buffer, int32 len);
	virtual void	OnSend(const BYTE* buffer, int32 len) abstract;
	int32			Recv();
	virtual void	OnRecv(BYTE* buffer, int32 len) abstract;

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
	WSAEVENT	_event;
	Address		_addr;
	ServiceRef	_serviceRef;

	int32		_recvLen = 0;
	BYTE		_recvBuffer[RECVSIZE];
};