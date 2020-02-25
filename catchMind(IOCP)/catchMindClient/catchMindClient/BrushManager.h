#pragma once
#include "Singleton.h"
#include "..//..//Common/Protocol.h"
struct Brush
{
	Color color;
	POINT pos;
	POINT oldPos;
	int thickness;
};
class BrushManager : public Singleton<BrushManager>
{
private:
	HWND			hWnd;
	vector<Brush*>  brush;

	bool			myTurn;
public:
	Color			color;
	POINT			pt;
	POINT			oldPt;
	int				thickness;
public:
	void			initBrush(HWND _hWnd);
	void			saveBrushPosition(Brush brs);
	void			drawBrush();
	void			renderBrush(HDC hdc);

	COLORREF		setBrushColor(Color _color);

	void			removeBoard();

	inline void		changeMyTurn(bool turn) { myTurn = turn; };
	inline bool		checkMyTurn() { return myTurn; };


};

