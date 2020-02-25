#pragma once
#include "Singleton.h"
class InputManager :public Singleton<InputManager>
{
private:
	HWND		hWnd;
	RECT		rect;
	bool		lButton;
	POINT		pt;
public:
	void		init(HWND _hWnd);
	void		inputKeyState();
	void		drawDotBrush();
	void		drawBrush();
	inline bool checkLButton()const{ return lButton; };
	inline RECT	getlButtonRect() const { return rect; };
};

