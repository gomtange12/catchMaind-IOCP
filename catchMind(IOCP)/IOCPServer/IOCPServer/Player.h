#pragma once
#include "Define.h"

struct PlayerInfo
{
public:
	int				 id;
	SOCKET			 socket;
	bool			 connected;
	std::string		 nickName;
	bool			 joinRoom;
public:
	OverData		 recvOverData;
	unsigned char	 packetBuf[MAX_BUFFER];
	int				 prevSize;
public:
	void			initPlayer();
	void			overlappedRecv();
};

