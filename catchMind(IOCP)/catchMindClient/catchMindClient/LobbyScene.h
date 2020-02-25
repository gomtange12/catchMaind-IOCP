#pragma once
#include "Scene.h"

class Lobby;
class LobbyScene : public Scene
{
private:
	Lobby* lobby;
public:

	void initScene();
	void updateScene();
	void renderScene(HDC hdc);
	void releaseScene();
	void setCheckButton(bool check);
};

