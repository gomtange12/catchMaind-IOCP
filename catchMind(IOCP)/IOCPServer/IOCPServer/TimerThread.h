#pragma once
//#include "MyThread.h"
//#include <queue>
//#include <mutex>
//
//struct Event
//{
//	int time;
//	int type;
//	int id;
//	int roomN;
//};
//class Comp
//{
//public:
//	Comp() {};
//	bool operator() (Event lhs, Event rhs) const {
//		return (lhs.time > rhs.time);
//	}
//
//};
//
//class TimerThread : public MyThread
//{
//private:
//	std::mutex timerLock;
//	std::priority_queue <Event, std::vector<Event>, Comp> timerQueue;
//public:
//	TimerThread();
//	virtual ~TimerThread();
//
//	void initThread();
//	void procThread();
//
//	void AddTimer(int id, int type, int roomN, int time);
//	void PopTimer(int roomN);
//};

