#include "pch.h"
#include "Address.h"

/*--------------
	NetAddress
---------------*/

Address::Address(SOCKADDR_IN sockAddr) : _sockAddr(sockAddr)
{
}

Address::Address(wstring ip, uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr = Ip2Address(ip.c_str());
	_sockAddr.sin_port = ::htons(port);
}

Address::Address(uint16 port)
{
	::memset(&_sockAddr, 0, sizeof(_sockAddr));
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	_sockAddr.sin_port = ::htons(port);
}

wstring Address::GetIpAddress()
{
	WCHAR buffer[100];
	::InetNtopW(AF_INET, &_sockAddr.sin_addr, buffer, sizeof(buffer)/sizeof(WCHAR));
	return wstring(buffer);
}

IN_ADDR Address::Ip2Address(const WCHAR* ip)
{
	IN_ADDR address;
	::InetPtonW(AF_INET, ip, &address);
	return address;
}