#include "stdafx.h"
#include "ResManager.h"
#include "BitMap.h"

void ResManager::initRes(HDC hdc)
{
	lobbyBitMap.reserve(LOBBY_RES_END);
	ingameBitMap.reserve(INGAME_RES_END);
	initLobbyRes(hdc);
	initIngameRes(hdc);
}
void ResManager::release()
{
	for (auto iter = lobbyBitMap.begin(); iter != lobbyBitMap.end(); ++iter) {
		(*iter)->release();
		delete *iter;
	}
	lobbyBitMap.clear();

	for (auto iter = ingameBitMap.begin(); iter != ingameBitMap.end(); ++iter) {
		(*iter)->release();
		delete *iter;
	}
	ingameBitMap.clear();
}

void ResManager::initLobbyRes(HDC hdc)
{

	initLobbyResId();

	for (int i = 0; i < LOBBY_RES_END; i++)
	{
		BitMap* bMap = new BitMap();
		resId[i] = "res\\" + resId[i] + ".bmp";
		bMap->init(hdc, resId[i]);
		lobbyBitMap.emplace_back(bMap);
	}
	resId.clear();

}
BitMap* ResManager::getLobbyBitMap(int index)
{
	return lobbyBitMap[index];
}

void ResManager::initLobbyResId()
{
	resId = { "lobbyBack", "roomUI"};
}

void ResManager::initIngameRes(HDC hdc)
{

	initIngameResId();

	for (int i = 0; i < INGAME_RES_END; i++)
	{
		BitMap* bMap = new BitMap();
		resId[i] = "res\\" + resId[i] + ".bmp";
		bMap->init(hdc, resId[i]);
		ingameBitMap.emplace_back(bMap);
	}
	resId.clear();

}
BitMap* ResManager::getIngameBitMap(int index)
{
	return ingameBitMap[index];
}

void ResManager::initIngameResId()
{
	resId = { "ingame","turn","chatBalloon" };
}