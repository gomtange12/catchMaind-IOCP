#include "stdafx.h"
#include "RoomManager.h"
#include "Room.h"

void RoomManager::init()
{
	matchRoomNum = -1;
}

void RoomManager::makeNewRoom(int roomNum)
{
	Room* nRoom = new Room();
	nRoom->initRoom(roomNum);
	room.insert(make_pair(roomNum, nRoom));
	if (matchRoomNum == -1)
		matchRoomNum = roomNum;
}
bool RoomManager::joinRoom(RECT otherRect)
{
	for (auto iter = room.begin(); iter != room.end(); iter++) {
		if ((*iter).second->joinRoom(otherRect)) {
			matchRoomNum = (*iter).first;
			return true;
		}
	}
	return false;
}

void RoomManager::renderRoom(HDC hdc)
{
	for (auto iter = room.begin(); iter != room.end(); iter++)
		(*iter).second->renderRoom(hdc);
}

void RoomManager::exitMatch()
{
	if (matchRoomNum != -1)
		room.find(matchRoomNum)->second->exitRoom();
	matchRoomNum = -1;
}
void RoomManager::matchRoom() {
	room.find(matchRoomNum)->second->matchRoom();
}
void RoomManager::removeRoom(int roomNum) {
	delete room.find(roomNum)->second;
	room.erase(roomNum);

}
void RoomManager::releaseRoom()
{
	for (auto iter = room.begin(); iter != room.end(); iter++)
		delete (*iter).second;
	room.clear();
}
