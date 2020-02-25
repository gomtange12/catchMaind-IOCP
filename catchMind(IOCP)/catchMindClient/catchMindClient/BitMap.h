#pragma once

class BitMap
{
private:
	HDC			memDC;
	HBITMAP		bitMap;
	HBITMAP		oldBitMap;
	SIZE        btsize;
public:
	void		init(HDC hdc, std::string fileName);
	void		render(HDC hdc, float x, float y);
	void		release();

};

