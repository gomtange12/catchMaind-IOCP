#pragma once
#include "Singleton.h"
#define MAX_ROOMNUM 8
struct Brush;
class Room;
class RoomManager : public Singleton<RoomManager>
{
private:
	std::map<int, Room*> room;
public:
	void		initRoom();
	void		makeNewRoom(int id);
	void		checkAlreadyMadeRoom(int id);
	void		joinRoom(int id, int rNum);
	void		joinRoomObserver(int id, int rNum);
	void		drawBrushInRoom(int id, Brush brush);
	void		changeColor(int id, Color color);
	void		removeBoard(int id);
	void		exitRoom(int id);
	void		giveupTurn(int id);
	void		sendChatJoinRoomUser(int id, std::string chat);
	void		releaseRoom();
};

