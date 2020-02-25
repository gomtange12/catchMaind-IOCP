#pragma once
#include "Singleton.h"
#define MAX_PLAYER 8

class Player;
class PlayerManager : public Singleton<PlayerManager>
{
private:
	vector<Player*>		player;

	string				myNick;
public:
	int					myTurnId;
public:
	void		initPlayer();
	
	void		joinPlayer(string nickName);
	void		exitPlayer();
	void		exitOtherPlayer(string nickName);
	void		changeTurn(int num);
	void		renderPlayer(HDC hdc);
	void		updatePlayer();

	void		setMyNick(string nick) { myNick = nick; };
	void		releasePlayer();

};

