#pragma once

#define RECVSIZE 1024

#ifdef _DEBUG
#define xalloc(size)		PoolAllocator::Alloc(size)
#define xrelease(ptr)		PoolAllocator::Release(ptr)
#else
#define xalloc(size)		BaseAllocator::Alloc(size)
#define xrelease(ptr)		BaseAllocator::Release(ptr)
#endif


/*---------------
	  Crash
---------------*/

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

#define ASSERT_CRASH(expr)			\
{									\
	if (!(expr))					\
	{								\
		CRASH("ASSERT_CRASH");		\
		__analysis_assume(expr);	\
	}								\
}


/*---------------
	SingleTon
---------------*/

#define SINGLETON(classname)							\
private:												\
	classname() {}										\
	classname(const classname& tmp) {}					\
	classname& operator=(const classname& tmp) { }		\
	~classname() {}										\
public:													\
	static classname* GetInstance() {					\
		static classname thread;						\
		return &thread;									\
	}													\

#define GET_SINGLE(classname)	classname::GetInstance()
#define THREAD					GET_SINGLE(ThreadManager)