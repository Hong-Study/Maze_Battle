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

	vector<SessionRef>	_sessions;
	vector<WSAEVENT>	_wsaEvents;
};

class ClientService : public Service
{
	using Super = Service;
public:
	ClientService(Address addr, SessionFactory factory);
	virtual ~ClientService() { }

	void Init(int32 count);
	virtual void Start() override;
};

class ServerService : public Service
{
	using Super = Service;
public:
	ServerService(Address addr, SessionFactory factory);
	virtual ~ServerService() { }

	void Listen();
	virtual void Start() override;
};