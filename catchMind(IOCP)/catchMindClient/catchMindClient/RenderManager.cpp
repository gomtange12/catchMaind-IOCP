#include "stdafx.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "ResManager.h"

void RenderManager::init(HWND _hWnd)
{
	hdc = GetDC(_hWnd);
	hWnd = _hWnd;

	memDC[0] = CreateCompatibleDC(hdc);
	bitmap[0] = CreateCompatibleBitmap(hdc, SCREENWIDTH, SCREENHIGHT);
	oldBitmap[0] = (HBITMAP)SelectObject(memDC[0], bitmap[0]);

	memDC[1] = CreateCompatibleDC(memDC[0]);
	bitmap[1] = (HBITMAP)LoadImage(NULL, "res\\back.bmp", IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	oldBitmap[1] = (HBITMAP)SelectObject(memDC[1], bitmap[1]);

	ResManager::getInstance()->initRes(memDC[0]);

}

void RenderManager::render()
{
	hdc = GetDC(hWnd);
	SetBkMode(memDC[0], TRANSPARENT);
	BitBlt(memDC[0], 0, 0, SCREENWIDTH, SCREENHIGHT, memDC[1], 0, 0, SRCCOPY);
	//==
	SceneManager::getInstance()->renderScene(memDC[0]);
	//==
	BitBlt(hdc, 0, 0, SCREENWIDTH, SCREENHIGHT, memDC[0], 0, 0, SRCCOPY);

	ReleaseDC(hWnd, hdc);
	
}

void RenderManager::release()
{

	for (int i = 0; i < 2; i++)
	{
		SelectObject(memDC[i], oldBitmap[i]);
		DeleteObject(bitmap[i]);
		DeleteDC(memDC[i]);
	}

	ResManager::getInstance()->release();
	ResManager::getInstance()->releaseInstance();

}
