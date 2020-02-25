#pragma once
//#include "Singleton.h"
#include "Chat.h"
class LobbyChat: public Chat
{
private:
	string		nickName;
public:
	void	 initChat();
	void	 recvChat(string& _chat);
	void	 pushEndterKey();
	void	 render(HDC hdc);
	void	 removeOutOfindex();
	void	 releaseChat();
	void	 setMyNickName(string& nick);
};

