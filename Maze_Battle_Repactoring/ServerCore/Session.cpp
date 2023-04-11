#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SendBuffer.h"

Session::~Session()
{
	_serviceRef = nullptr;
}

int32 Session::Send(SendBufferRef buffer)
{
	int32 sendLen = 0;
	int32 size = buffer->GetSize();
	_sendBufferRef = buffer;

	OnSend(buffer->Data(), size);

	while (true) {
		if (sendLen = ::send(_socket, reinterpret_cast<char*>(buffer->Data()), size, 0) == SOCKET_ERROR) {
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			cout << "ERROR" << endl;
			
			return SOCKET_ERROR;
		}
		break;
	}
	
	return sendLen;
}

int32 Session::Recv()
{
	int32 _recvLen = 0;
	while (true) {
		_recvLen = recv(_socket, reinterpret_cast<char*>(_recvBuffer.WritePos()), _recvBuffer.FreeSize(), 0);
		if (_recvLen == SOCKET_ERROR) {
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			return SOCKET_ERROR;
		}
		break;
	}
	if (_recvBuffer.OnWrite(_recvLen)) {
		int processLen = OnRecv(_recvBuffer.ReadPos(), _recvBuffer.DataSize());
		if (processLen < 0 || _recvBuffer.OnRead(processLen) == false)
			cout << "Read Overflow" << endl;
	}
	else
	{
		cout << "Write Overflow" << endl;
	}

	_recvBuffer.Clean();
	return _recvLen;
}

void Session::Disconnect()
{
	OnDisconnected();

	::SocketUtils::Close(_socket);
}

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;
	while (true) {
		int32 dataSize = len - processLen;
		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader* header = reinterpret_cast<PacketHeader*>(&buffer[processLen]);

		if (header->size < dataSize)
			break;

		OnRecvPacket(&buffer[processLen], header->size);

		processLen += header->size;
	}

	return processLen;
}
