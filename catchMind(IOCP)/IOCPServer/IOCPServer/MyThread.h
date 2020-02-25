#pragma once

class MyThread
{	
public:
	virtual ~MyThread() {};
public:
	virtual void initThread() = 0;
	virtual void procThread() = 0;

	virtual void joinThread() { mythread.join(); }
	
protected:
	std::thread mythread;

};

