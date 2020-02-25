#pragma once
#include "Singleton.h"
class Chat;
class ChatManager :public Singleton<ChatManager>
{
private:
	map<SCENE_NUM, Chat*>   chat;
	SCENE_NUM				sceneNum;
public:
	void		initChat();
	void		pushWord(WPARAM wParam);
	void		pushEndterKey();
	void		pushRemoveKey();
	void		recvChat(string& _chat);
	void		setMyNickName(string & nick);
	void		updateChat();
	void		setInGameChatBalloonPosition(int num);
	void		render(HDC hdc);
	void		changeSceneNum(SCENE_NUM _sceneNum) { sceneNum = _sceneNum; };
	void		releaseChat();
};

