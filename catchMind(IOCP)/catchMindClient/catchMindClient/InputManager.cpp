#include "stdafx.h"
#include "InputManager.h"
#include "BrushManager.h"

void InputManager::init(HWND _hWnd)
{
	hWnd = _hWnd;
	lButton = false;
}

void InputManager::inputKeyState()
{

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (lButton == false) {
			lButton = true;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			rect = { pt.x, pt.y, pt.x + 1, pt.y + 1 };

			drawDotBrush();
		
		}
		else {
			lButton = true;
			GetCursorPos(&pt);
			ScreenToClient(hWnd, &pt);
			rect = { -1, -1, -1, -1 };
			
			drawBrush();
		}
		
	}
	else {
		lButton = false;
		rect = { -1, -1, -1, -1 };
	}
}
void InputManager::drawDotBrush() {
	if (BrushManager::getInstance()->checkMyTurn()) {
		if (745 >= pt.x && pt.x >= 250 && 507 >= pt.y && pt.y >= 195) {
			BrushManager::getInstance()->pt = pt;
			BrushManager::getInstance()->oldPt.x = pt.x + 1;
			BrushManager::getInstance()->oldPt.y = pt.y + 1;
			BrushManager::getInstance()->drawBrush();
		}
	}
}

void InputManager::drawBrush()
{
	if (BrushManager::getInstance()->checkMyTurn())
		if (745 >= pt.x && pt.x >= 250 && 507 >= pt.y && pt.y >= 195)
			BrushManager::getInstance()->pt = pt;
}
