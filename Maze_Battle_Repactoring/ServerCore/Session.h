#pragma once
#include "Address.h"
#include "RecvBuffer.h"

class Session : public enable_shared_from_this<Session>
{
public:
	Session() : _recvBuffer(1024) {  }
	virtual ~Session();

	int32			Send(SendBufferRef buffer);
	int32			Recv();
	void			Disconnect();

	virtual void	OnConnected() { }
	virtual void	OnDisconnected() { }
	virtual int32	OnSend(BYTE* buffer, int32 len) { return len; }
	virtual int32	OnRecv(BYTE* buffer, int32 len) { return len; }
	
public:
	SOCKET&			GetSocket() { return _socket; }
	void			SetSocket(SOCKET socket) { _socket = socket; }
	WSAEVENT		GetEvent() { return _event; }
	void			SetEvent(WSAEVENT event) { _event = event; }
	Address&		GetAddr() { return _addr; }
	void			SetAddr(Address addr) { _addr = addr; }
	ServiceRef		GetService() { return _serviceRef; }
	void			SetService(ServiceRef ref) { _serviceRef = ref; }
	bool			IsConnected() { return _socket != SOCKET_ERROR; }

private:
	SOCKET			_socket = SOCKET_ERROR;
	WSAEVENT		_event = 0;
	Address			_addr;
	ServiceRef		_serviceRef;
	RecvBuffer		_recvBuffer;
	SendBufferRef	_sendBufferRef;
};

class PacketSession : public Session
{
public:
	PacketSession() { }
	~PacketSession() { }

protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) abstract = 0;
};
