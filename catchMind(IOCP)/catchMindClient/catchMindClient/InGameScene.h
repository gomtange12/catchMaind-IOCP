#pragma once
#include "Scene.h"

class BitMap;

struct ColorButton {
	RECT rect;
	int color;
};
class InGameScene : public Scene
{
private:
	BitMap*				back;

	RECT				exitButtonRect;
	bool				exitCheck;
	RECT				removeBoardButton;
	RECT				giveupButton;
	vector<ColorButton*> colorButton;

public:

	void	initScene();
	void	initIngameButtons();
	void	updateScene();
	void	renderScene(HDC hdc);
	void	checkPushRemoveButton();
	void	checkPushGiveupButton();
	void	checkPushColorButton();	
	void	releaseScene();
	void	checkPushExitButton();
	void	releaseButton();
	void	setCheckButton(bool check);
};

