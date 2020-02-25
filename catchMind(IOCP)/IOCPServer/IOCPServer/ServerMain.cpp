#include "pch.h"
#include "IOCPServer.h"
#include "ThreadManager.h"

int main()
{
	system("chcp 949");

	IOCPServer::getInstance()->initNetwork();

	ThreadManager::getInstance()->createThreads();
	ThreadManager::getInstance()->joinThreads();

	IOCPServer::getInstance()->releaseNetwork();
	IOCPServer::getInstance()->releaseInstance();

	return 0;
}
