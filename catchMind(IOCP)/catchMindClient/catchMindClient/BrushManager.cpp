#include "stdafx.h"
#include "BrushManager.h"
#include "InputManager.h"
#include "PacketManager.h"
void BrushManager::initBrush(HWND _hWnd)
{
	hWnd = _hWnd;
	color = BLACK;
	myTurn = false;
	thickness = 3;
}

void BrushManager::saveBrushPosition(Brush brs) {
	Brush* nBrush = new Brush();
	nBrush->color = color;
	nBrush->pos = brs.pos;
	nBrush->oldPos = brs.oldPos;

	if (color == WHITE)
		nBrush->thickness = 15;
	else
		nBrush->thickness = 3;

	brush.push_back(nBrush);
}
void BrushManager::drawBrush() 
{
	Brush nBrush;
	nBrush.pos = pt;
	nBrush.oldPos = oldPt;
	PacketManager::getInstance()->drawBrushPkt(nBrush);
}
void BrushManager::renderBrush(HDC hdc) 
{
	HPEN MyPen, oldPen;
	COLORREF color;
	for (auto iter = brush.begin(); iter != brush.end(); ++iter)
	{
		color = setBrushColor((*iter)->color);
		MyPen = CreatePen(PS_SOLID, (*iter)->thickness, color);
		oldPen = (HPEN)SelectObject(hdc, MyPen);

		MoveToEx(hdc, (*iter)->pos.x, (*iter)->pos.y, NULL);
		LineTo(hdc, (*iter)->oldPos.x, (*iter)->oldPos.y);
		ReleaseDC(hWnd, hdc);

		SelectObject(hdc, oldPen);
		DeleteObject(MyPen);
	}

}
COLORREF BrushManager::setBrushColor(Color _color) 
{
	COLORREF color;
	switch (_color)
	{
	case BLACK:
		color = RGB(0, 0, 0);
		break;
	case RED:
		color = RGB(255, 0, 0);
		break;
	case BLUE:
		color = RGB(0, 0, 255);
		break;
	case GREEN:
		color = RGB(0, 255, 0);
		break;
	case YELLOW:
		color = RGB(255, 255, 0);
		break;
	case WHITE:
		color = RGB(255, 255, 255);
		break;
	}

	return color;
}
void BrushManager::removeBoard() {
	for (auto &iter : brush)
		delete iter;
	brush.clear();
}