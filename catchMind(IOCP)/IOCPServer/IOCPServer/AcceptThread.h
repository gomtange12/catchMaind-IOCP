#pragma once
#include "MyThread.h"
#define MAX_USER 20
class AcceptThread : public MyThread
{
private:
	int userNum =-1;
public:

	void initThread();
	void procThread();

};

