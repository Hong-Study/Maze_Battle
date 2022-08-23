#pragma once
#include "pch.h"

struct Datas
{
public:
	Datas(SOCKET sock) :_sock(sock), _index(0) { 
		loby = new Loby_Data;
	}
	~Datas() {
		cout << "Á¾·á" << endl;
	}

	SOCKET& GetSocket() { return _sock; }
	void SetIndex(int index) { _index = index; }
	int GetIndex() { return _index; }

	Loby_Data* GetLoby_Data() { return loby; }

private:
	SOCKET _sock;
	//NetAddress netAddress;
	int _index;
	Loby_Data* loby;
};