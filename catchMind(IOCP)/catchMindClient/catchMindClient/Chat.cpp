#include "stdafx.h"
#include "Chat.h"
#include "PacketManager.h"

void Chat::pushWord(WPARAM wParam)
{
	if ((TCHAR)wParam != VK_RETURN && (TCHAR)wParam != VK_BACK)
		str.push_back((TCHAR)wParam);
}

void Chat::pushRemoveKey()
{
	if (str.size() > 0)
		str.pop_back();
}
void Chat::recvChat(string& _chat)
{
	chat.push_back(_chat);
}
void Chat::setInGameChatBalloonPosition(int num)
{
}
void Chat::setMyNickName(string& nick)
{
}
void Chat::update()
{
}
