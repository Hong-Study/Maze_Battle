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
	void Connect();
	virtual void Start() override;

	int32 Send(SendBufferRef buf);
private:
	void Close();

private:
	SessionRef _session;
	WSAEVENT _event;
};

class ServerService : public Service
{
	using Super = Service;
public:
	ServerService(Address addr, SessionFactory factory);
	virtual ~ServerService() { _sessions.clear(); _wsaEvents.clear(); }

	void Listen();
	virtual void Start() override;

private:
	void Disconnect(int32 index);

	vector<SessionRef>	_sessions;
	vector<WSAEVENT>	_wsaEvents;
};