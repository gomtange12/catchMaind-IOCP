#pragma once
class BitMap;
class Room
{
private:
	BitMap*		bitmap;
	POINT		position;
	int			rNum;
	bool		match;
	RECT		rect;
public:
	void		initRoom(int num);
	bool		joinRoom(RECT otherRect);
	void		renderRoom(HDC hdc);
	inline void matchRoom() { match = true; }
	inline void exitRoom() { match = false; };
};

