#pragma once
#include "Scene.h"

class LoginScene :public Scene
{
private:
	
public:
	void initScene();
	void updateScene();
	void renderScene(HDC hdc);
	void releaseScene();
	void setCheckButton(bool check);
};

