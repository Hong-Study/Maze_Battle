#include "pch.h"
#include "Global.h"
#include "ThreadManager.h"
#include "Memory.h"

extern Memory* GMemory = nullptr;

class Global
{
public:
	Global()
	{
		
		GMemory = new Memory();
	}
	~Global()
	{
		delete GMemory;
	}
private:

}GGlobal;