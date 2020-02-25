#pragma once
#include "MyThread.h"

class WorkerThread : public MyThread
{
private:
	
public:

	void initThread();
	void procThread();

	void error_display(const char *msg, int err_no);


};

