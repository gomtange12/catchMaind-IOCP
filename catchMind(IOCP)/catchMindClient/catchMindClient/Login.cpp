#include "stdafx.h"
#include "Login.h"
#include "PacketManager.h"
#include "sha1.h"

void Login::initLogin(HWND hWnd, HINSTANCE hInst) 
{
	idEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, 410, 310, 200, 25, hWnd, (HMENU)ID_EDIT_ID, hInst, NULL);

	pwEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, 410, 340, 200, 25, hWnd, (HMENU)ID_EDIT_PW, hInst, NULL);

	logninBT = CreateWindow(TEXT("button"), TEXT("Login"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		510, 370, 100, 25, hWnd, (HMENU)ID_BUTTON_LOGIN, hInst, NULL);
}

void Login::loginInfo(char* id, char* pw)
{
	string idStr;
	string pwStr;

	for (int i = 0; i < 50; ++i) {
		idStr.push_back(id[i]);
		if (idStr[i] == '\0')
			break;
	}

	for (int i = 0; i < 50; ++i) {
		pwStr.push_back(pw[i]);
		if (pwStr[i] == '\0')
			break;
	}

	passwordHash(idStr, pwStr);
}
void Login::getWinText(char* id, char* pw, int size =50)
{
	GetWindowText(idEdit, id, size);
	GetWindowText(pwEdit, pw, size);
}

void Login::passwordHash(string& id, string& pw) 
{
	string hashId = sha1(id);
	string hashPw = sha1(pw);
	PacketManager::getInstance()->LoginPkt(hashId, hashPw);
	
}
void Login::hideLoginWindow()
{
	ShowWindow(idEdit, SW_HIDE);
	ShowWindow(pwEdit, SW_HIDE);
	ShowWindow(logninBT, SW_HIDE);
}