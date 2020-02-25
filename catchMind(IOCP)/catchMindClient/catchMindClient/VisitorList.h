#pragma once
#include "Singleton.h"
class VisitorList :public Singleton<VisitorList>
{
private:
	SCENE_NUM		sceneNum;
	string			myNick;
	list<string>	otherNick;
	list<int>		roomJoinId;
public:
	void	renderVisitorList(HDC hdc);
	void	myIdRender(HDC hdc);
	void	lobbyVisitorListRender(HDC hdc);
	void	roomExitId();
	void	disconnetId(string id);

public:
	inline void setSceneNum(SCENE_NUM _sceneNum) { sceneNum = _sceneNum; }
	inline void setMyNick(string nick) { myNick = nick; };
	inline void setOtherId(string nick) { otherNick.push_back(nick); };
	inline void setRoomJoinId(int id) { roomJoinId.push_back(id); };

};

