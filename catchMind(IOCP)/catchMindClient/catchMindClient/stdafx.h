// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once
#include "targetver.h"
#pragma comment(lib, "msimg32.lib")
#pragma comment (lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARINGS
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

#include <WinSock2.h>
// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <deque>
#include <chrono>
// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
using namespace std;
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WM_SOCKET (WM_USER+1)
#define BUFSIZE 1024

#define SCREENWIDTH 1015
#define SCREENHIGHT 780

#define ID_EDIT_ID 100
#define ID_EDIT_PW 101
#define ID_BUTTON_LOGIN 102

enum SCENE_NUM {
	SCENE_LOGIN,
	SCENE_LOBBY,
	SCENE_GAME,
	SCENE_END
};
enum LOBBY_RES_ID {
	LOBBY_RES_BACK,
	LOBBY_RES_ROOMUI,
	LOBBY_RES_END
};
enum INGAME_RES_ID {
	INGAME_RES_BACK,
	INGAME_RES_TURN,
	INGAME_RES_CHAT,
	INGAME_RES_END
};
