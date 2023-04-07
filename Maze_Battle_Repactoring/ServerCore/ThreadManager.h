#pragma once
#include <thread>
#include <functional>
#include "CoreMacro.h"

class ThreadManager
{
	SINGLETON(ThreadManager);

public:
	void Push(function<void()> f);
	void Join();

private:
	vector<std::thread> _threads;
};

