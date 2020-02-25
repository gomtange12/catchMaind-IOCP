#pragma once
#include "Singleton.h"

class Login : public Singleton<Login>
{
private:
	HWND	idEdit;
	HWND	pwEdit;
	HWND	logninBT;
public:

	void	initLogin(HWND hWnd, HINSTANCE hInst);
	void	loginInfo(char * id, char * pw);
	void	getWinText(char * id, char * pw, int size);
	void	passwordHash(string & id, string & pw);
	void	hideLoginWindow();

};

