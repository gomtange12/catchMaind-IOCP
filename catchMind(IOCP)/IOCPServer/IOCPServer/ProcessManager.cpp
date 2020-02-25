#include "pch.h"
#include "Define.h"
#include "ProcessManager.h"
#include "PacketManager.h"
#include "Login.h"
#include "PlayerManager.h"
#include "RoomManager.h"

void ProcessManager::processPacket(int key, unsigned char* ptr)
{
	switch (ptr[1])  //type
	{
		case CS_PACKET_INDEX_LOGIN_INFO:
		{
			processLogin(key, ptr);	
			break;
		}
		case CS_PACKET_INDEX_MAKE_ROOM:
		{
			processMakeRoom(key, ptr);
			break;
		}
		case CS_PACKET_INDEX_JOIN_ROOM:
		{
			processJoinRoom(key, ptr);
			break;
		}
		case CS_PACKET_INDEX_DRAW_BOARD:
		{
			processDrawBoard(key, ptr);
		
			break;
		}
		case CS_PACKET_INDEX_CHANGE_COLOR:
		{
			processChangeColor(key,ptr);
			break;
		}
		case CS_PACKET_INDEX_REMOVE_BOARD:
		{
			processRemoveBoard(key, ptr);
			break;
		}
		case CS_PACKET_INDEX_EXIT_ROOM:
		{
			processExitRoom(key, ptr);
			break;
		}
		case CS_PACKET_INDEX_CHAT_LOBBY:
		{
			processChatLoobby(key, ptr);
			break;
		}
		case CS_PACKET_INDEX_CHAT_INGAME:
		{
			processChatInGame(key, ptr);
			break;
		}

		case CS_PACKET_INDEX_GIVEUP_TURN:
		{
			processGiveupTurn(key,ptr);
			break;
		}
	}
}

void ProcessManager::processLogin(int key, unsigned char* ptr)
{
	CS_PAKET_LOGIN_INFO *pkt = reinterpret_cast<CS_PAKET_LOGIN_INFO *>(ptr);
	std::string logId;
	std::string pwd;

	for (int i = 0; i < (80 / 2); ++i) {
		logId.push_back(pkt->id[i]);
		pwd.push_back(pkt->pw[i]);
	}
	std::string nickName = Login::getInstance()->findAndLoingInfoApply(logId, pwd);
	if (nickName == "#Unknown")
		return;

	PlayerManager::getInstance()->setPlayerNickName(key, nickName);
	PlayerManager::getInstance()->loginInformAllUsers(key, nickName);
	PacketManager::getInstance()->changeScenePacket(key, SCENE_LOBBY);

	RoomManager::getInstance()->checkAlreadyMadeRoom(key);
}

void ProcessManager::processMakeRoom(int key, unsigned char* ptr)
{
	RoomManager::getInstance()->makeNewRoom(key);
}

void ProcessManager::processJoinRoom(int key, unsigned char* ptr)
{
	CS_PAKET_JOIN_ROOM *pkt = reinterpret_cast<CS_PAKET_JOIN_ROOM *>(ptr);
	RoomManager::getInstance()->joinRoom(key, (int)pkt->rNum);
}

void ProcessManager::processDrawBoard(int key, unsigned char* ptr)
{
	CS_PAKET_DRAW_BOARD *pkt = reinterpret_cast<CS_PAKET_DRAW_BOARD *>(ptr);
	Brush brs;
	brs.pos.x = pkt->posX;
	brs.pos.y = pkt->posY;
	brs.oldPos.x = pkt->oldPosX;
	brs.oldPos.y = pkt->oldPosY;
	RoomManager::getInstance()->drawBrushInRoom(key, brs);
}

void ProcessManager::processChangeColor(int key, unsigned char * ptr)
{
	CS_PAKET_CHANGE_COLOR *pkt = reinterpret_cast<CS_PAKET_CHANGE_COLOR *>(ptr);
	RoomManager::getInstance()->changeColor(key, (Color)pkt->color);
}

void ProcessManager::processRemoveBoard(int key, unsigned char * ptr)
{
	RoomManager::getInstance()->removeBoard(key);
}

void ProcessManager::processExitRoom(int key, unsigned char * ptr)
{
	RoomManager::getInstance()->exitRoom(key);
}

void ProcessManager::processChatLoobby(int key, unsigned char * ptr)
{
	CS_PAKET_CHAT_LOBBY *pkt = reinterpret_cast<CS_PAKET_CHAT_LOBBY *>(ptr);
	std::string chat;
	for (int i = 0; i < pkt->len; ++i) {
		chat.push_back(pkt->chat[i]);
	}
	PlayerManager::getInstance()->informChatAllUsers(chat);
}

void ProcessManager::processChatInGame(int key, unsigned char * ptr)
{
	CS_PAKET_CHAT_INGAME *pkt = reinterpret_cast<CS_PAKET_CHAT_INGAME *>(ptr);
	std::string chat;
	for (int i = 0; i < pkt->len; ++i) {
		chat.push_back(pkt->chat[i]);
	}
	RoomManager::getInstance()->sendChatJoinRoomUser(key, chat);
}

void ProcessManager::processGiveupTurn(int key, unsigned char * ptr)
{
	RoomManager::getInstance()->giveupTurn(key);
}
