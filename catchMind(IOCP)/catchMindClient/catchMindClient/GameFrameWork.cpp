#include "stdafx.h"
#include "GameFrameWork.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "BrushManager.h"

void GameFrameWork::init(HWND _hWnd)
{
	hWnd = _hWnd;

	TimerManager::getInstance()->initTime();

	InputManager::getInstance()->init(hWnd);

	RenderManager::getInstance()->init(hWnd);

	SceneManager::getInstance()->initScene();

	BrushManager::getInstance()->initBrush(hWnd);

	
}
void GameFrameWork::release()
{
	InputManager::getInstance()->releaseInstance();

	SceneManager::getInstance()->releaseScene();
	SceneManager::getInstance()->releaseInstance();


	RenderManager::getInstance()->release();
	RenderManager::getInstance()->releaseInstance();

	TimerManager::getInstance()->releaseInstance();
}

void GameFrameWork::update()
{
	if (TimerManager::getInstance()->updateTime())
		return;

	InputManager::getInstance()->inputKeyState();
	SceneManager::getInstance()->updateScene();
	RenderManager::getInstance()->render();
	

}

