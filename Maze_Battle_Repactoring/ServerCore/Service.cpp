#include "pch.h"
#include "Service.h"
#include "Session.h"
#include <memory>

Service::Service(Address addr, SessionFactory factory)
	: _addr(addr) , _factory(factory)
{
	_sessions.reserve(100);
}

void Service::SessionSetting(SessionRef session, SOCKET socket, Address& addr, WSAEVENT event)
{
	session->SetSocket(socket);
	session->SetAddr(addr);
	session->SetEvent(event);
	session->SetService(shared_from_this());

	session->OnConnected();
}

ClientService::ClientService(Address addr, SessionFactory factory)
	:Super(addr, factory)
{
	
}


void ClientService::Connect(const int32 count)
{
	for (int i = 0; i < count; i++) {
		SOCKET socket = SocketUtils::CreateSocket();

		if (socket == INVALID_SOCKET)
			cout << "Socket Create Failed" << endl;

		if (SocketUtils::NonBlockingSet(socket))
			cout << "CreateListenSocket Failed" << endl;

		while (true)
		{
			if (SocketUtils::Connect(socket, _addr))
			{
				// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
				if (::WSAGetLastError() == WSAEWOULDBLOCK)
					continue;
				// 이미 연결된 상태라면 break
				if (::WSAGetLastError() == WSAEISCONN)
					break;
				// Error
				break;
			}
		}

		WSAEVENT event = ::WSACreateEvent();
		if (SOCKET_ERROR == ::WSAEventSelect(socket, event, FD_WRITE | FD_READ | FD_CLOSE))
			cout << "EventSlect Failed" << endl;

		SessionRef session = _factory();
		SessionSetting(session, socket, _addr, event);

		_sessions.push_back(session);
		_wsaEvents.push_back(event);
	}
}

void ClientService::Start()
{
	while (true)
	{
		int32 index = ::WSAWaitForMultipleEvents(_wsaEvents.size(), &_wsaEvents[0], FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
			continue;

		index -= WSA_WAIT_EVENT_0;
		WSANETWORKEVENTS networkEvent;

		if (::WSAEnumNetworkEvents(_sessions[index]->GetSocket(), _wsaEvents[index], &networkEvent) == SOCKET_ERROR)
			continue;

		if (networkEvent.lNetworkEvents & FD_READ)
		{
			if ((networkEvent.lNetworkEvents & FD_READ) && (networkEvent.iErrorCode[FD_READ_BIT] != 0)) {
				cout << "Continue" << endl;
				continue;
			}

			SessionRef session = _sessions[index];
			if (session->Recv() == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK)
			{
				cout << "Recv Error" << endl;
				continue;
			}
		}

		if (networkEvent.lNetworkEvents & FD_CLOSE)
		{
			if ((networkEvent.lNetworkEvents & FD_CLOSE) && (networkEvent.iErrorCode[FD_CLOSE_BIT] != 0))
				continue;

			_sessions.erase(_sessions.begin() + index);
			_wsaEvents.erase(_wsaEvents.begin() + index);
		}
	}
}

ServerService::ServerService(Address addr, SessionFactory factory)
	: Super(addr, factory)
{
	
}

void ServerService::Listen()
{
	SOCKET _listenSocket = SocketUtils::CreateSocket();
		
	if (SocketUtils::NonBlockingSet(_listenSocket))
		cout << "CreateLitenSocket Failed" << endl;

	if (_listenSocket == INVALID_SOCKET)
		cout << "Socket Create Failed" << endl;

	if (SocketUtils::Bind(_listenSocket, _addr))
		cout << "Bind Failed" << endl;

	if (SocketUtils::Listen(_listenSocket))
		cout << "Listen Failed" << endl;

	WSAEVENT event = ::WSACreateEvent();

	if (SOCKET_ERROR == ::WSAEventSelect(_listenSocket, event, FD_ACCEPT | FD_CLOSE))
		cout << "Event Select Error" << endl;

	SessionRef session = _factory();
	SessionSetting(session, _listenSocket, _addr, event);

	_sessions.push_back(session);
	_wsaEvents.push_back(event);
}

void ServerService::Start()
{	
	while (true)
	{
		int32 index = ::WSAWaitForMultipleEvents(_wsaEvents.size(), &_wsaEvents[0], FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
			continue;

		index -= WSA_WAIT_EVENT_0;
		WSANETWORKEVENTS networkEvent;

		if (::WSAEnumNetworkEvents(_sessions[index]->GetSocket(), _wsaEvents[index], &networkEvent) == SOCKET_ERROR)
			continue;
		
		if (networkEvent.lNetworkEvents & FD_ACCEPT)
		{
			if (networkEvent.iErrorCode[FD_ACCEPT_BIT] != 0)
				continue;

			SOCKADDR_IN addr;
			int32 addrLen = sizeof(addr);

			SOCKET clientSocket = ::accept(_sessions[index]->GetSocket(), (SOCKADDR*)&addr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				WSAEVENT clientEvent = ::WSACreateEvent();
				if (SOCKET_ERROR == ::WSAEventSelect(clientSocket, clientEvent, FD_WRITE | FD_READ | FD_CLOSE))
					cout << "Event Select Error" << endl;
				
				SessionRef session = _factory();
				SessionSetting(session, clientSocket, _addr, clientEvent);

				_sessions.push_back(session);
				_wsaEvents.push_back(clientEvent);

				cout << "Connect Success" << endl;
			}
			else 
			{
				cout << "Accept Failed" << endl;
			}
		}

		if (networkEvent.lNetworkEvents & FD_READ)
		{
			if ((networkEvent.lNetworkEvents & FD_READ) && (networkEvent.iErrorCode[FD_READ_BIT] != 0)) {
				cout << "Continue" << endl;
				continue;
			}

			SessionRef session = _sessions[index];
			if (session->Recv() == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK)
			{
				cout << "Recv Error" << endl;
				continue;
			}
		}

		if (networkEvent.lNetworkEvents & FD_CLOSE)
		{
			cout << "Delete " << index << endl;
			_sessions.erase(_sessions.begin() + index);
			_wsaEvents.erase(_wsaEvents.begin() + index);
		}
	}
}
