#include "pch.h"
#include "PlayerManager.h"
#include "Player.h"
#include "PacketManager.h"
#include "Login.h"
void PlayerManager::initPlayer()
{
	for (int i = 0; i < MAX_USER; ++i) {
		PlayerInfo* nPlayer = new PlayerInfo();
		nPlayer->initPlayer();
		player.insert(std::make_pair(i, nPlayer));
	}
}
bool PlayerManager::giveAcceptPlayerId()
{
	int id = 0;
	for (auto iter = player.begin(); iter != player.end(); ++iter, ++id) {
		if ((*iter).second->connected == false) {
			(*iter).second->id = id;
			std::cout << " Client Accept ID : " << id << std::endl;
			return true;
		}
	}
	return false;
}
bool PlayerManager::checkConnected(int id) 
{
	return player.find(id)->second->connected;
}
void PlayerManager::connectPlayer(int id) 
{
	player.find(id)->second->connected = true;
}
void PlayerManager::setPlayerSock(int id, SOCKET& sock) 
{
	player.find(id)->second->socket=sock;
}
SOCKET& PlayerManager::getPlayerSock(int id)
{
	return player.find(id)->second->socket;
}

int PlayerManager::getPrevSize(int id)
{
	return player.find(id)->second->prevSize;
}
void PlayerManager::setPrevSize(int id, int size)
{
	player.find(id)->second->prevSize = size;
}
unsigned char* PlayerManager::getPacketBuf(int id)
{
	return player.find(id)->second->packetBuf;
}

void PlayerManager::setPlayerNickName(int id,std::string nick)
{
	player.find(id)->second->nickName=nick;
}
void PlayerManager::loginInformAllUsers(int id, std::string nick)
{
	for (auto &iter : player) {
		if (iter.second->connected && iter.second->nickName != "#Unknown") {
			PacketManager::getInstance()->loginSuccessfulAndNicknamePacket(id, iter.first, nick);
			if ( id != iter.first) {
				PacketManager::getInstance()->loginSuccessfulAndNicknamePacket(iter.first, id, iter.second->nickName);
			}
		}
	}
}
void PlayerManager::informMakeRoomAllUsers(int roomNum)
{
	for (auto &iter : player) {
		if (iter.second->connected)
			PacketManager::getInstance()->makeNewRoomPacket(iter.first, roomNum);
	}
}
void PlayerManager::informRemoveRoomAllUsers(int roomNum)
{
	for (auto &iter : player) {
		if (iter.second->connected)
			PacketManager::getInstance()->removeRoomPacket(iter.first, roomNum);
	}
}

void PlayerManager::informChatAllUsers(std::string chat)
{
	for (auto &iter : player) {
		if (iter.second->connected&& iter.second->joinRoom==false)
			PacketManager::getInstance()->sendLobbyChatPacket(iter.first, chat);
	}
}
void PlayerManager::checkInRoom(int id, bool check)
{
	player.find(id)->second->joinRoom=check;
}

void PlayerManager::informDisconnetClient(int id)
{
	player.find(id)->second->connected=false;
	Login::getInstance()->logoutDisconnectId(player.find(id)->second->nickName);
	for (auto &iter : player) {
		if (iter.second->connected && iter.first != id) {
			PacketManager::getInstance()->disconnectClientPacket(id, iter.first);
		}
	}
}
void PlayerManager::overlappedRecv(int id)
{
	player.find(id)->second->overlappedRecv();
}
void PlayerManager::releasePlayer()
{
	for (auto &iter : player)
		delete iter.second;

	player.clear();
}