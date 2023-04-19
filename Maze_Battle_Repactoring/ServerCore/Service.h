#pragma once
#include <functional>

using SessionFactory = function<SessionRef(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(Address addr, SessionFactory factory);
	virtual ~Service() { }

	void SessionSetting(SessionRef session, SOCKET socket, Address& addr, WSAEVENT event);
	virtual void Start() abstract;
	virtual void Close() abstract;

protected:
	SessionFactory		_factory;
	Address				_addr;
};

class ClientService : public Service
{
	using Super = Service;
public:
	ClientService(Address addr, SessionFactory factory);
	virtual ~ClientService() { }
	bool Connect();
	virtual void Start() override;
	virtual void Close() override;

	int32 Send(SendBufferRef buf);

private:
	SessionRef _session;
	WSAEVENT _event;
};

class ServerService : public Service
{
	using Super = Service;
public:
	ServerService(Address addr, SessionFactory factory, int32 miliSecond = 10);
	virtual ~ServerService() { Close();}

	void Listen();
	virtual void Start() override;
	virtual void Close() override;

private:
	void Disconnect(int32 index);

private:
	vector<SessionRef>	_sessions;
	vector<WSAEVENT>	_wsaEvents;
	atomic<bool>		_IsStart = false;
	int32				_miliSecond = 0;
	thread*				_thread = nullptr;
};