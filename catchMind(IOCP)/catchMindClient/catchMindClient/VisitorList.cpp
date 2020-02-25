#include "stdafx.h"
#include "VisitorList.h"

void VisitorList::renderVisitorList(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	myIdRender(hdc);
	if (sceneNum == SCENE_LOBBY)
		lobbyVisitorListRender(hdc);

}
void VisitorList::myIdRender(HDC hdc) {
	string myID = { "MY ID :" };
	TextOut(hdc, 828, 106, myID.c_str(), (int)myID.length());

	TextOut(hdc, 878, 106, myNick.c_str(), (int)myNick.length());
}
void VisitorList::lobbyVisitorListRender(HDC hdc) {
	string visitorList = { "대기실 접속자  :" };
	TextOut(hdc, 736, 226, visitorList.c_str(), (int)visitorList.length());

	int i = 0;
	for (auto iter = otherNick.begin(); iter != otherNick.end(); ++iter, ++i)
		TextOut(hdc, 736, (15 * i) + 246, (*iter).c_str(), (int)(*iter).length());
	
}

void VisitorList::roomExitId()
{
	roomJoinId.clear();
}
void VisitorList::disconnetId(string id)
{
	for (auto iter = otherNick.begin(); iter != otherNick.end();)
	{
		if (id == (*iter))
			iter = otherNick.erase(iter);
		else
			++iter;
	}
}
