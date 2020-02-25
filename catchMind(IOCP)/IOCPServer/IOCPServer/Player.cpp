#include "pch.h"
#include "Player.h"


void PlayerInfo::initPlayer()
{
	id = -1;
	connected = false;
	joinRoom = false;
	nickName = { "#Unknown" };
	prevSize = 0;
	recvOverData.todo = OP_RECV;
	recvOverData.wsaBuf.buf = (CHAR*)recvOverData.iocpBuf;
	recvOverData.wsaBuf.len = sizeof(recvOverData.iocpBuf);
}
void PlayerInfo::overlappedRecv()
{
	DWORD flags = 0;
	ZeroMemory(&recvOverData.wsaOver, sizeof(WSAOVERLAPPED));

	WSARecv(socket, &recvOverData.wsaBuf,
		1, NULL, &flags, &recvOverData.wsaOver, 0);
}
