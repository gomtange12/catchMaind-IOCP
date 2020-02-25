#include "pch.h"
#include "IOCPServer.h"
#include "PlayerManager.h"
#include "Login.h"
#include "RoomManager.h"
#include "Question.h"
void IOCPServer::initNetwork()
{
	Login::getInstance()->initLoginInfo();

	Question::getInstance()->initQuestion();

	PlayerManager::getInstance()->initPlayer();

	RoomManager::getInstance()->initRoom();

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

}
void IOCPServer::releaseNetwork() 
{
	Login::getInstance()->releaseInstance();

	Question::getInstance()->releaseInstance();

	RoomManager::getInstance()->releaseRoom();
	RoomManager::getInstance()->releaseInstance();

	PlayerManager::getInstance()->releasePlayer();
	PlayerManager::getInstance()->releaseInstance();

	WSACleanup();
}




