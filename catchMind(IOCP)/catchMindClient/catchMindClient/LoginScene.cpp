#include "stdafx.h"
#include "LoginScene.h"
#include "Login.h"
void LoginScene::initScene()
{

}

void LoginScene::updateScene()
{

}

void LoginScene::renderScene(HDC hdc)
{
	SetTextColor(hdc, RGB(255, 255, 255));
	string myID = { "ID :" };
	TextOut(hdc, 375, 312, myID.c_str(), (int)myID.length());
	string myPW = { "PW :" };
	TextOut(hdc, 373, 342, myPW.c_str(), (int)myPW.length());

}

void LoginScene::releaseScene()
{
}

void LoginScene::setCheckButton(bool check)
{
}
