#include "pch.h"
//#include "TimerThread.h"
//#include "IOCPServer.h"
//#include "Define.h"
//
//TimerThread::TimerThread()
//{
//	
//}
//
//TimerThread::~TimerThread()
//{
//}
//void TimerThread::initThread()
//{
//	mythread = std::thread([&]() { TimerThread::procThread(); });
//}
//void TimerThread::procThread()
//{
//	
//	while (true) 
//	{
//		std::this_thread::sleep_for(std::chrono::duration<float>(0.01f));
//		while (false == timerQueue.empty())
//		{
//			if (timerQueue.top().time >= GetTickCount()) break;
//			timerLock.lock();
//			Event ev = timerQueue.top();
//			timerQueue.pop();
//			timerLock.unlock();
//			stOverEx *ex = new stOverEx;
//			ex->m_todo = ev.type;
//			ex->id = ev.id;
//			ex->roomNum = ev.roomN;
//			PostQueuedCompletionStatus(IOCPSERVER->GetIocp(), 1, NULL, &ex->m_wsaOver);
//		}
//	}
//}
//void TimerThread::AddTimer(int id, int type, int roomN, int time)
//{
//	timerLock.lock();
//	timerQueue.push(Event{ time, type, id ,roomN});
//	timerLock.unlock();
//}
//void TimerThread::PopTimer(int roomN)
//{
//	timerLock.lock();
//	timerQueue.pop();
//	timerLock.unlock();
//	stOverEx *ex = new stOverEx;
//	//ex->m_todo = OP_STOP;
//	ex->roomNum = roomN;
//	PostQueuedCompletionStatus(IOCPSERVER->GetIocp(), 1, NULL, &ex->m_wsaOver);
//}