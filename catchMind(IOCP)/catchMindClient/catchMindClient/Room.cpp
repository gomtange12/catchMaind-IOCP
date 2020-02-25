#include "stdafx.h"
#include "Room.h"
#include "BitMap.h"
#include "ResManager.h"
#include "PacketManager.h"

void Room::initRoom(int num)
{
	rNum = num;
	bitmap = ResManager::getInstance()->getLobbyBitMap(LOBBY_RES_ROOMUI);
	position.x = ((num % 2) * 331) + 22;
	position.y = ((num / 2) * 94) + 255;

	rect = { position.x + 1, position.y + 1, position.x + 326, position.y + 89 };
	match = false;
}


bool Room::joinRoom(RECT otherRect)
{
	if (match)
		return false;

	RECT temp;
	if (IntersectRect(&temp, &rect, &otherRect)) {
		PacketManager::getInstance()->joinRoomPkt(rNum);
		return true;
	}
	return false;
}

void Room::renderRoom(HDC hdc)
{
	bitmap->render(hdc, (float)position.x, (float)position.y);
	
}