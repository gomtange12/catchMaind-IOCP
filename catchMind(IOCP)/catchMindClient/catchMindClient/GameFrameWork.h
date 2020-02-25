#pragma once
#include "Singleton.h"

class GameFrameWork : public Singleton<GameFrameWork>
{
private:
	HWND		hWnd;
public:

	void	 init(HWND _hWnd);
	void	 release();
	void	 update();
};

