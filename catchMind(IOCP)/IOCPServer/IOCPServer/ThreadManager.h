#pragma once
#include "Singleton.h"
#define WORKER_THREAD_NUM 4

class MyThread;
class ThreadManager : public Singleton<ThreadManager>
{
private:
	std::vector <MyThread*> threads;
public:
	void createThreads();
	void addThread(MyThread* myth);
	void joinThreads();
	
	MyThread* findThread(int TNum) {
		return threads[TNum];
	}
};