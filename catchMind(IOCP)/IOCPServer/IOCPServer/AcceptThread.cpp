#include "pch.h"
#include "AcceptThread.h"
#include "PacketManager.h"
#include "IOCPServer.h"
#include "PlayerManager.h"


void AcceptThread::initThread()
{
	mythread = std::thread([&]() { AcceptThread::procThread(); });
}
void AcceptThread::procThread()
{
	int retval;

	SOCKET listenSocket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("Error - Invalid socket\n");
		exit(1);
		return;
	}

	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9000);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	retval = bind(listenSocket, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(SOCKADDR_IN));
	if (retval == SOCKET_ERROR)
	{
		std::cout << "err on bind" << std::endl;
		return;
	}
	retval = listen(listenSocket, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		std::cout << "err on listen" << std::endl;
		return;
	}

	while (1)
	{
		SOCKET clientSocket;
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(SOCKADDR_IN);
		ZeroMemory(&clientAddr, sizeof(SOCKADDR_IN));

		clientSocket = WSAAccept(listenSocket, reinterpret_cast<sockaddr *>(&clientAddr), &addrLen,0,0);
		
		//네이글 알고리즘
		//int flag = TRUE;
		//setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag));
	
		if (clientSocket == INVALID_SOCKET)
		{
			std::cout << "Error - Accept Failure\n";
			exit(1);
		};
		++userNum;
		if (PlayerManager::getInstance()->giveAcceptPlayerId()==false) {
			std::cout << " ==MAX USER== \n";
			closesocket(clientSocket);
			--userNum;
			continue;
		}
		PlayerManager::getInstance()->setPlayerSock(userNum, clientSocket);

		//
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(PlayerManager::getInstance()->getPlayerSock(userNum)),
			IOCPServer::getInstance()->getIocp(), userNum, 0);
		//
		PlayerManager::getInstance()->connectPlayer(userNum);
		//
		
		PacketManager::getInstance()->connectPacket(userNum); 
		
		PlayerManager::getInstance()->overlappedRecv(userNum);
	}
}
