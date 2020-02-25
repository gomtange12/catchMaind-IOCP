#include "stdafx.h"
#include "ChatManager.h"
#include "Chat.h"
#include "LobbyChat.h"
#include "InGameChat.h"
void ChatManager::initChat()
{
	sceneNum = SCENE_LOBBY;

	chat.insert(make_pair(SCENE_LOBBY, new LobbyChat()));
	chat.insert(make_pair(SCENE_GAME, new InGameChat()));

	for (auto &iter : chat)
		iter.second->initChat();
}
void ChatManager::pushWord(WPARAM wParam) 
{
	chat.find(sceneNum)->second->pushWord(wParam);
}

void ChatManager::pushEndterKey()
{
	chat.find(sceneNum)->second->pushEndterKey();
}

void ChatManager::pushRemoveKey()
{
	chat.find(sceneNum)->second->pushRemoveKey();
}

void ChatManager::recvChat(string& _chat)
{
	chat.find(sceneNum)->second->recvChat(_chat);
}
void ChatManager::setMyNickName(string& nick)
{
	chat.find(sceneNum)->second->setMyNickName(nick);
}
void ChatManager::updateChat()
{
	chat.find(sceneNum)->second->update();
}
void ChatManager::setInGameChatBalloonPosition(int num)
{
	chat.find(sceneNum)->second->setInGameChatBalloonPosition(num);
}
void ChatManager::render(HDC hdc)
{
	chat.find(sceneNum)->second->render(hdc);
}

void ChatManager::releaseChat()
{
	for (auto &iter : chat) {
		iter.second->releaseChat();
		delete iter.second;
	}

	chat.clear();
}
