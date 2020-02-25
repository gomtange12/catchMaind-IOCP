#include "stdafx.h"
#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::initPlayer()
{
	myNick = "Unknown";
	for (int i = 0; i < MAX_PLAYER; ++i) {
		Player* nPlayer = new Player();
		nPlayer->init();
		player.push_back(nPlayer);
	}
}

void PlayerManager::joinPlayer(string nickName)
{
	int joinNum = 0;

	for (auto &iter : player) {		
		joinNum++;
		if (iter->getJoinNum() == -1) {
			iter->setPosition(joinNum);
			iter->setNickName(nickName);

			if (myNick == nickName)
				myTurnId = joinNum;

			return;
		}
	}
	
}
void PlayerManager::exitPlayer() {
	for (auto &iter : player) 
		iter->setPosition(-1);	
}
void PlayerManager::exitOtherPlayer(string nickName)
{
	for (auto &iter : player)
		if (iter->getNickName() == nickName)
			iter->setPosition(-1);
	
}
void PlayerManager::changeTurn(int num) {
	for (auto &iter : player) {
		if (iter->getJoinNum() == num) 
			iter->chageTurn(true);
		else 
			iter->chageTurn(false);
	}
}
void PlayerManager::renderPlayer(HDC hdc) 
{	
	for (auto &iter : player)
		iter->render(hdc);
}
void PlayerManager::updatePlayer()
{
	for (auto &iter : player)
		iter->update();
}

void PlayerManager::releasePlayer()
{
	for (auto &iter : player)
		delete iter;
	player.clear();
}
