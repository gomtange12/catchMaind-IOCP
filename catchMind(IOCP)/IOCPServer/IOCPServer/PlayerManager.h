#pragma once
#include "Singleton.h"
#define MAX_USER 20

struct PlayerInfo;
class PlayerManager :public Singleton<PlayerManager>
{
private:
	std::map<int, PlayerInfo*> player;
public:
	void			initPlayer();
	bool			giveAcceptPlayerId();
	bool			checkConnected(int id);
	void			connectPlayer(int id);
	void			setPlayerSock(int id, SOCKET & sock);
	SOCKET&			getPlayerSock(int id);
	int				getPrevSize(int id);
	void			setPrevSize(int id, int size);
	unsigned char*  getPacketBuf(int id);
	void			setPlayerNickName(int id, std::string nick);
	void			loginInformAllUsers(int id, std::string nick);
	void			informMakeRoomAllUsers(int id);
	void			informRemoveRoomAllUsers(int roomNum);
	void			informChatAllUsers(std::string chat);
	void			checkInRoom(int id,bool check);
	void			informDisconnetClient(int id);
	void			overlappedRecv(int id);
	void			releasePlayer();
};

