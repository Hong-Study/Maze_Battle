#include "pch.h"
#include "ThreadManager.h"

void ThreadManager::Init()
{

}

void ThreadManager::Push(function<void()> f)
{
	_threads.emplace_back(f);
}

void ThreadManager::Join()
{
	for (int i = 0; i < _threads.size(); i++) 
	{
		if(_threads[i].joinable())
			_threads[i].join();
	}
}
