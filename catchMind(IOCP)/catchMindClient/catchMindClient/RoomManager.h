#pragma once
#include "Singleton.h"
class Room;
class RoomManager :public Singleton<RoomManager>
{
private:
	map<int, Room*> room;
	int				matchRoomNum;
public:
	void			init();
	void			makeNewRoom(int roomNum);
	bool			joinRoom(RECT otherRect);
	void			renderRoom(HDC hdc);
	void			exitMatch();
	void			matchRoom();
	void			removeRoom(int roomNum);
	void			releaseRoom();
};

