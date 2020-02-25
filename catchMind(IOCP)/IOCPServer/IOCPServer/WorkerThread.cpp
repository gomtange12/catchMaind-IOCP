#include "pch.h"
#include "Define.h"
#include "WorkerThread.h"
#include "PacketManager.h"
#include "IOCPServer.h"
#include "ThreadManager.h"
#include "PlayerManager.h"
#include "ProcessManager.h"

void WorkerThread::initThread()
{
	mythread = std::thread([&]() { WorkerThread::procThread(); });
}
void WorkerThread::procThread()
{

	while (true)
	{
		DWORD ioSize;
		unsigned long long key;
		OverData *over;
		int ret = GetQueuedCompletionStatus(IOCPServer::getInstance()->getIocp(), &ioSize, &key,
			reinterpret_cast<WSAOVERLAPPED**>(&over), INFINITE);

		// 俊矾贸府
		if (0 == ret) {
			int err_no = GetLastError();
			if (64 == err_no) {
				PlayerManager::getInstance()->informDisconnetClient((int)key);
				
			}
			else error_display("GQCS : ", err_no);
			continue;
		}
		//立加辆丰 贸府
		if (0 == ioSize) {
			PlayerManager::getInstance()->informDisconnetClient((int)key);
			closesocket(PlayerManager::getInstance()->getPlayerSock((int)key));
			continue;
		}

		if (OP_RECV == over->todo) {

			int restData = ioSize;
			unsigned char *ptr = over->iocpBuf;
			int packetSize = 0;
			if (0 != PlayerManager::getInstance()->getPrevSize((int)key))
				packetSize = PlayerManager::getInstance()->getPacketBuf((int)key)[0];

			while (restData > 0) {
				if (0 == packetSize) packetSize = ptr[0];
				int needSize = packetSize - PlayerManager::getInstance()->getPrevSize((int)key);
				if (restData >= needSize) {

					memcpy(PlayerManager::getInstance()->getPacketBuf((int)key)
						+ PlayerManager::getInstance()->getPrevSize((int)key),
						ptr, needSize);

					//
					ProcessManager::getInstance()->processPacket((int)key, PlayerManager::getInstance()->getPacketBuf((int)key));
					//

					ptr += needSize;
					restData -= needSize;
					packetSize = 0;
					PlayerManager::getInstance()->setPrevSize((int)key, 0);
				}
				else {
					memcpy(PlayerManager::getInstance()->getPacketBuf((int)key)
						+ PlayerManager::getInstance()->getPrevSize((int)key),
						ptr, restData);
					ptr += restData;
					PlayerManager::getInstance()->setPrevSize((int)key, PlayerManager::getInstance()->getPrevSize((int)key) + restData);
					restData = 0;
				}
			}
			PlayerManager::getInstance()->overlappedRecv((int)key);
		}
		else if (OP_SEND == over->todo) {
			delete over;
		}

	}
}
void WorkerThread::error_display(const char *msg, int err_no)
{
	WCHAR *lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	std::cout << msg;
	std::cout << "俊矾 " << lpMsgBuf << std::endl;
	while (true);
	LocalFree(lpMsgBuf);
}