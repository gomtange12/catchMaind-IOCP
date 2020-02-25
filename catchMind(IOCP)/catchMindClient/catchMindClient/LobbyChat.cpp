#include "stdafx.h"
#include "LobbyChat.h"
#include "PacketManager.h"
void LobbyChat::initChat() {

}

void LobbyChat::recvChat(string& _chat) {
	chat.push_back(_chat);
	removeOutOfindex();
}
void LobbyChat::pushEndterKey() {

	if (str.size() > 0) {
		str = nickName + str;
		PacketManager::getInstance()->sendLobbyChatPkt(str);
		str.clear();
	}
}
void LobbyChat::render(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));
	int i = 0;
	for (auto iter = chat.rbegin(); iter != chat.rend(); ++iter,++i) {
		TextOut(hdc,740, (-15*i)+632, (*iter).c_str(), (int)(*iter).length());
	}
	TextOut(hdc, 760, 651, str.c_str(), (int)str.length());
}
void LobbyChat::removeOutOfindex() 
{
	if (chat.size() > 7)
		chat.pop_front();
}

void LobbyChat::releaseChat()
{
	chat.clear();
}
void LobbyChat::setMyNickName(string& nick)
{
	nickName = nick;
	nickName.push_back(' ');
	nickName.push_back(':');
	nickName.push_back(' ');
}
