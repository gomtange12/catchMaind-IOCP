#pragma once
#include "Singleton.h"

class BitMap;
class ResManager:public Singleton<ResManager>
{
private:
	vector<string> resId;
	vector<BitMap*> lobbyBitMap;
	vector<BitMap*> ingameBitMap;
public:
	void initRes(HDC hdc);
	void release();

	//Lobby
	void initLobbyRes(HDC hdc);
	void initLobbyResId();
	BitMap* getLobbyBitMap(int index);

	//Ingame
	void initIngameRes(HDC hdc);
	void initIngameResId();
	BitMap * getIngameBitMap(int index);

};

