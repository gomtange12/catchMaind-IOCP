#include "stdafx.h"
#include "InGameChat.h"
#include "ResManager.h"
#include "BitMap.h"
#include "PacketManager.h"
#include "BrushManager.h"
void InGameChat::initChat()
{
	bitmap = ResManager::getInstance()->getIngameBitMap(INGAME_RES_CHAT);
	chatPos.x = -200;
	chatPos.y = -200;
}

void InGameChat::recvChat(string & _chat)
{
	GameChat* nGameChat = new GameChat();
	nGameChat->chat = _chat;
	nGameChat->pos = chatPos;
	nGameChat->count = 0;
	chat.push_back(nGameChat);	
}
void InGameChat::pushEndterKey() {
	if (BrushManager::getInstance()->checkMyTurn()) {
		str.clear();
		return;
	}

	if (str.size() > 0) {
		PacketManager::getInstance()->sendInGameChatPkt(str);
		str.clear();
	}
}
void InGameChat::setInGameChatBalloonPosition(int num)
{
	if(num <= 4)
		chatPos.x = 209;
	if (num >= 5)
		chatPos.x = 677;

	if(num==1||num==5)
		chatPos.y = 194;
	if(num==2||num==6)
		chatPos.y = 300;
	if(num==3||num==7)
		chatPos.y = 408;
	if(num==4||num==8)
		chatPos.y = 515;

	if (num == 0)
	{
		chatPos.x = 798;
		chatPos.y = 619;
	}

}
void InGameChat::update()
{
	removeTimeOutAnswer();
}
void InGameChat::render(HDC hdc)
{	
	renderChatBalloon(hdc);

	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, 493, 649, str.c_str(), (int)str.length());
}
void InGameChat::renderChatBalloon(HDC hdc) {
	for (auto &iter : chat) {
		bitmap->render(hdc, (float)iter->pos.x, (float)iter->pos.y);
		int len = 0;
		if (iter->chat.length() > 12)
			len = 12;
		else
			len = (int)iter->chat.length();
		TextOut(hdc, iter->pos.x + 10, iter->pos.y + 14, iter->chat.c_str(), len);
	}
}
void InGameChat::removeTimeOutAnswer()
{
	for (auto &iter : chat) {
		iter->count += 1;
		if (iter->count > 80) {
			delete iter;
			chat.pop_front();
		}
	}
}

void InGameChat::releaseChat()
{
	for (auto &iter : chat)
		delete iter;
	chat.clear();
}
