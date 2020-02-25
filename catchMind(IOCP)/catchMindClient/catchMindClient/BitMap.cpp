#include "stdafx.h"
#include "BitMap.h"


void BitMap::init(HDC hdc, std::string fileName)
{
	memDC = CreateCompatibleDC(hdc);
	bitMap = (HBITMAP)LoadImage(NULL, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	oldBitMap = (HBITMAP)SelectObject(memDC, bitMap);


	BITMAP tbitmap;
	GetObject(bitMap, sizeof(tbitmap), &tbitmap);
	btsize.cx = tbitmap.bmWidth;
	btsize.cy = tbitmap.bmHeight;
}

void BitMap::render(HDC hdc, float x, float y)
{
	TransparentBlt(hdc, (int)x, (int)y, (int)btsize.cx, (int)btsize.cy, memDC, 0, 0, (int)btsize.cx, (int)btsize.cy, RGB(255, 0, 255));
}
void BitMap::release()
{
	SelectObject(memDC, oldBitMap);
	DeleteObject(bitMap);
	DeleteDC(memDC);

}
