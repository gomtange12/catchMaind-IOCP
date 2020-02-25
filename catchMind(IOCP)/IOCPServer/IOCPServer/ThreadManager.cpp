#include "pch.h"
#include "ThreadManager.h"
#include "MyThread.h"
#include "WorkerThread.h"
#include "AcceptThread.h"
#include "TimerThread.h"


void ThreadManager::createThreads()
{
	std::cout << " :: Thereads ::\n";
	std::cout << "  AcceptTheread\n";
	addThread(new AcceptThread); 

	std::cout << "  WorkerThreads\n";

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	for (int i = 0; i < (int)si.dwNumberOfProcessors * 2; ++i)
		addThread(new WorkerThread);
	
	//std::cout << "  TimerTheread\n";
	//addThread(new TimerThread); 
}
void ThreadManager::addThread(MyThread* myth)
{
	myth->initThread();
	threads.emplace_back(myth);
}
void ThreadManager::joinThreads() {
	for (auto &th : threads) {
		th->joinThread();
		delete th;
	}

	
}


