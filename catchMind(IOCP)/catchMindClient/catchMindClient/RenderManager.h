#pragma once
#include "Singleton.h"
class RenderManager: public Singleton<RenderManager>
{
private:
	HWND		hWnd;
	HDC			hdc;
	HDC			memDC[2];
	HBITMAP		bitmap[2];	//0 Back 1 BackGround
	HBITMAP		oldBitmap[2];

public:

	void	init(HWND _hWnd);
	void	render();
	void	release();
};

