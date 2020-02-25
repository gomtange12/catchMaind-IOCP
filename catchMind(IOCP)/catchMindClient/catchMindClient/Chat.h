#pragma once
class Chat
{
protected:
	string			str;
	deque<string>   chat;
public:
	virtual void	initChat()=0;
	virtual void	pushEndterKey()=0;
	virtual void	render(HDC hdc)=0;
	virtual void	releaseChat() = 0;
public:
	virtual void	pushWord(WPARAM wParam);
	virtual void	pushRemoveKey();
	virtual void	recvChat(string& _chat);
	virtual void	setInGameChatBalloonPosition(int num);
	virtual void	setMyNickName(string& nick);
	virtual void	update();
};

