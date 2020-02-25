#include "stdafx.h"
#include "TimerManager.h"


void TimerManager::initTime()
{
	lastTime = std::chrono::system_clock::now();
}

bool TimerManager::updateTime()
{
	std::chrono::duration<float> sec = std::chrono::system_clock::now() - lastTime;
	/*if (sec.count() < (1 / FPS))
		return true;*/

	elapseTime = sec.count();
	lastTime = std::chrono::system_clock::now();
	return false;
}
