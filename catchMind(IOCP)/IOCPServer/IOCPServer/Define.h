#pragma once
#define MAX_BUFFER		1024

const int OP_RECV = 1;
const int OP_SEND = 2;

struct OverData { // 버퍼정보를구조체화.
	WSAOVERLAPPED wsaOver;
	WSABUF wsaBuf;
	unsigned char iocpBuf[MAX_BUFFER];
	unsigned char todo;
};

struct Brush
{
	Color color;
	POINT pos;
	POINT oldPos;
};

enum ThreadNum {
	ACCEPT_TH,
	WORKER_TH01,
	WORKER_TH02,
	//WORKER_TH03,
	//TIMER_TH
	THREAD_END
};
enum SCENE_NUM {
	SCENE_LOGIN,
	SCENE_LOBBY,
	SCENE_GAME,
	SCENE_END
};
