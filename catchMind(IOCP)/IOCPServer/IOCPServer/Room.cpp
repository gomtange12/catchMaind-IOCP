#include "pch.h"
#include "Define.h"
#include "Room.h"
#include "PacketManager.h"
#include "PlayerManager.h"
#include "Question.h"
void Room::initRoom(int rNum)
{
	roomNum = rNum;
	match = false;
	beMade = false;
	roomUserCount = 0;
	turnNum = 1;
	saveColor = BLACK;
}
bool Room::findVacancy(int id) 
{
	for (auto &iter : joinUserId) { 
		if (iter == -1)
		{
			iter = id;
			match = true;
			for (auto &iter : joinUserId)
				PacketManager::getInstance()->informMatchPacket(iter);
			return true;
		}
	}
	return false;
}
void Room::joinRoom(int id)
{
	roomUserCount++;
	if(!findVacancy(id))
		joinUserId.push_back(id);

	beMade = true;

	if (joinUserId.size() == MAX_JOIN_USER) {
		match = true;
		for (auto &iter : joinUserId) 
			PacketManager::getInstance()->informMatchPacket(iter);
	}
	PlayerManager::getInstance()->checkInRoom(id, true);
}
void Room::informQuestion()
{
	roomQuestion = Question::getInstance()->selectRandomQuestion();

	PacketManager::getInstance()->infromQuestionInfoPacket(joinUserId[turnNum-1], roomQuestion);
}
void Room::changeTurnRoom()
{
	if (MAX_JOIN_USER < turnNum)
		turnNum = 1;

	for (auto &iter : joinUserId)
		PacketManager::getInstance()->changeNextTurnPacket(iter, turnNum);
	
	informQuestion();
}
void Room::changeNextTurn() {
	turnNum++;
	changeTurnRoom();
}
void Room::exitRoom(int id)
{
	PlayerManager::getInstance()->checkInRoom(id, false);

	bool observer = checkObserver(id);

	roomUserCount--;
	checkRemoveRoom(id);
	
	for (auto iter = joinUserId.begin(); iter != joinUserId.end();) {
		
		if ((*iter) == id) {
			PacketManager::getInstance()->changeScenePacket(id,SCENE_LOBBY);
			if(observer)
				iter = joinUserId.erase(iter);
			else {
				(*iter) = -1;
				match = false;
			}
		}
		else {
			if (observer == false && (*iter) != -1) {
				PacketManager::getInstance()->changeNextTurnPacket((*iter), -1);
				PacketManager::getInstance()->exitRoomPacket(id, (*iter));
				turnNum = 1;
			}
			iter++;
			
		}
		
	}
	
}
bool Room::checkObserver(int id) 
{
	for (int i = 0; i < joinUserId.size(); ++i) {
		if (joinUserId[i] == id)
			if (i > MAX_JOIN_USER - 1)
				return true;
				
	}
	return false;
}
void Room::checkRemoveRoom(int id) {
	if (roomUserCount == 0) {
		PacketManager::getInstance()->changeScenePacket(id, SCENE_LOBBY);
		PlayerManager::getInstance()->informRemoveRoomAllUsers(roomNum);
		joinUserId.clear();
		removeBoard();
		saveScore.clear();
		initRoom(roomNum);
		return;
	}
}
void Room::informJoinRoomUsers(int id, bool observer)
{
	for (auto &iter : joinUserId) {
		PacketManager::getInstance()->informJoinUserPacket(iter, id);
		if (iter != id)
			PacketManager::getInstance()->informJoinUserPacket(id, iter);
	}
}

bool Room::checkInUser(int id) 
{
	for (auto &iter : joinUserId) {
		if (iter == id)
			return true;
	}
	return false;
}
void Room::changeColor(Color _color)
{
	saveColor = _color;
	for (auto &iter : joinUserId)
		PacketManager::getInstance()->changeColorPacket(iter, saveColor);
}
void Room::drawInformInUser(int id, Brush brs)
{
	Brush* nBrush = new Brush();
	nBrush->color = saveColor;
	nBrush->pos = brs.pos;
	nBrush->oldPos = brs.oldPos;

	saveBrush.push_back(nBrush);

	for (auto &iter : joinUserId)
		PacketManager::getInstance()->drawInformInRoomUserPacket(iter, brs);
}
void Room::sendSaveBrushJoinObserver(int id)
{
	for (auto &brushIter : saveBrush) {
		PacketManager::getInstance()->changeColorPacket(id, brushIter->color);
		PacketManager::getInstance()->drawInformInRoomUserPacket(id, *brushIter);
	}
}
void Room::sendSaveScoreJoinObserver(int id)
{
	for (auto &scoreIter : saveScore) 
		PacketManager::getInstance()->infromUsersGetScorePacket(scoreIter, id);
	
}
void Room::removeBoard()
{
	for (auto &iter : joinUserId) {
		if(iter != -1)
			PacketManager::getInstance()->removeBoardPacket(iter);
	}

	for (auto &iter : saveBrush)
		delete iter;
	saveBrush.clear();

}
void Room::sendChatJoinRoomUser(int id, std::string chat) 
{
	bool ret=checkForCorrectAnswers(id, chat);

	for (auto &iter : joinUserId) {
		if (iter != -1) {
			PacketManager::getInstance()->sendInGameChatPacket(id, iter, chat);
			if (ret) {
				PacketManager::getInstance()->infromUsersGetScorePacket(id, iter);
				saveScore.push_back(id);
			}
		}
	}
}
bool Room::checkForCorrectAnswers(int id, std::string chat) {

	if (roomQuestion == chat) {
		changeNextTurn();
		return true;
	}
	return false;
}

void Room::releaseRoom()
{
	for (auto &iter : saveBrush)
		delete iter;

	saveBrush.clear();
	saveScore.clear();
	joinUserId.clear();
	roomQuestion.clear();
}
