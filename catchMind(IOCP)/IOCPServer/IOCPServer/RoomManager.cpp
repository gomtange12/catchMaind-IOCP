#include "pch.h"
#include "Define.h"
#include "RoomManager.h"
#include "Room.h"
#include "PacketManager.h"
#include "PlayerManager.h"


void RoomManager::initRoom()
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		Room* nRoom = new Room();
		nRoom->initRoom(i);
		room.insert(std::make_pair(i, nRoom));
	}
}

void RoomManager::makeNewRoom(int id)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->beMade == false) {
			room.find(i)->second->joinRoom(id);
			PlayerManager::getInstance()->informMakeRoomAllUsers(i);
			room.find(i)->second->informJoinRoomUsers(id,false);
			PacketManager::getInstance()->changeScenePacket(id, SCENE_GAME);
			return;
		}
	}
}
void RoomManager::checkAlreadyMadeRoom(int id)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->beMade == true) {
			PacketManager::getInstance()->makeNewRoomPacket(id, i);
		}
	}
}
void RoomManager::joinRoom(int id, int rNum) 
{
	if (room.find(rNum)->second->match == false) { 
		room.find(rNum)->second->joinRoom(id);
		room.find(rNum)->second->informJoinRoomUsers(id,false);
		PacketManager::getInstance()->changeScenePacket(id, SCENE_GAME);

		if (room.find(rNum)->second->match == true) {
			room.find(rNum)->second->informQuestion();
			room.find(rNum)->second->changeTurnRoom();
		}
		return;
	}

	if (room.find(rNum)->second->match == true) {
		joinRoomObserver(id, rNum);
	}
}
void RoomManager::joinRoomObserver(int id, int rNum) {
	room.find(rNum)->second->joinRoom(id);
	room.find(rNum)->second->informJoinRoomUsers(id, true);
	PacketManager::getInstance()->changeScenePacket(id, SCENE_GAME);
	PacketManager::getInstance()->changeNextTurnPacket(id, room.find(rNum)->second->getTurnNum());
	room.find(rNum)->second->sendSaveBrushJoinObserver(id);
	room.find(rNum)->second->sendSaveScoreJoinObserver(id);
}
void RoomManager::drawBrushInRoom(int id, Brush brush) {
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->drawInformInUser(id, brush);
			return;
		}
	}
}
void RoomManager::changeColor(int id, Color color) {
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->changeColor(color);
			return;
		}
	}
}
void RoomManager::removeBoard(int id)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->removeBoard();
			return;
		}
	}
}
void RoomManager::exitRoom(int id)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->exitRoom(id);
			return;
		}
	}
}
void RoomManager::giveupTurn(int id)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->changeNextTurn();
			return;
		}
	}
}
void RoomManager::sendChatJoinRoomUser(int id, std::string chat)
{
	for (int i = 0; i < MAX_ROOMNUM; ++i) {
		if (room.find(i)->second->checkInUser(id)) {
			room.find(i)->second->sendChatJoinRoomUser(id,chat);
			return;
		}
	}
}
void RoomManager::releaseRoom()
{
	for (auto &iter : room) 
		delete iter.second;
	
	room.clear();
}
