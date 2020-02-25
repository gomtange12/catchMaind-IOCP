#pragma once
#include "Chat.h"

struct GameChat{
	POINT pos;
	string chat;
	int count;
};
class BitMap;
class InGameChat :public Chat
{
private:
	BitMap*				bitmap;
	deque<GameChat*>	chat;
	POINT				chatPos;
public:
	void		initChat();
	void		recvChat(string& _chat);
	void		pushEndterKey();
	void		setInGameChatBalloonPosition(int num);
	void		update();
	void		render(HDC hdc);
	void		renderChatBalloon(HDC hdc);
	void		removeTimeOutAnswer();
	void		releaseChat();
};

