#pragma once
#include "Singleton.h"
#define FPS			60.0f

class TimerManager :public Singleton<TimerManager>
{
private:
	chrono::system_clock::time_point lastTime;

	float							elapseTime;

public:
	void initTime();
	bool updateTime();

	inline float getElapseTime() const { return elapseTime; };

};

