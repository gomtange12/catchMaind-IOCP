#include "stdafx.h"
#include "Lobby.h"
#include "BitMap.h"
#include "ResManager.h"
#include "InputManager.h"
#include "PacketManager.h"
#include "VisitorList.h"
#include "RoomManager.h"
void Lobby::initLobby()
{
	back = ResManager::getInstance()->getLobbyBitMap(LOBBY_RES_BACK);
	
	RoomManager::getInstance()->init();

	makeNewRoomRect = { 622,119,707,199 };
	makeNewRoomCheckButton = false;
	joinRoomCheckButton = false;
}

void Lobby::updateLobby()
{
	makeNewRoomCheck();
	joinRoomCheck();
}

void Lobby::renderLobby(HDC hdc)
{
	back->render(hdc, 0, 0);

	RoomManager::getInstance()->renderRoom(hdc);

	VisitorList::getInstance()->renderVisitorList(hdc);
}

void Lobby::makeNewRoomCheck()
{
	if (InputManager::getInstance()->checkLButton() && makeNewRoomCheckButton ==false) {
		RECT temp;
		if (IntersectRect(&temp, &makeNewRoomRect, &InputManager::getInstance()->getlButtonRect())) {
			PacketManager::getInstance()->makeNewRoomPkt();
			makeNewRoomCheckButton = true;
		}
	}
}
void Lobby::joinRoomCheck() {
	if (InputManager::getInstance()->checkLButton()&& joinRoomCheckButton == false) {
		if(RoomManager::getInstance()->joinRoom(InputManager::getInstance()->getlButtonRect()))
			joinRoomCheckButton = true;
	}
}
void Lobby::release()
{
	VisitorList::getInstance()->releaseInstance();
	RoomManager::getInstance()->releaseRoom();
	RoomManager::getInstance()->releaseInstance();
}

void Lobby::setNewRoomButton(bool check)
{
	makeNewRoomCheckButton = check;
	joinRoomCheckButton = check;
}
