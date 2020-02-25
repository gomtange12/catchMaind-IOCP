#include "stdafx.h"
#include "InGameScene.h"
#include "PacketManager.h"
#include "InputManager.h"
#include "BitMap.h"
#include "ResManager.h"
#include "BrushManager.h"
#include "PlayerManager.h"
#include "PacketManager.h"
#include "Question.h"
#include "ScoreManager.h"
void InGameScene::initScene()
{
	back = ResManager::getInstance()->getIngameBitMap(INGAME_RES_BACK);

	PlayerManager::getInstance()->initPlayer();

	initIngameButtons();
	
	ScoreManager::getInstance()->initScore();
}
void InGameScene::updateScene()
{
	checkPushExitButton();
	checkPushColorButton();
	checkPushRemoveButton();
	checkPushGiveupButton();

	PlayerManager::getInstance()->updatePlayer();
}

void InGameScene::initIngameButtons()
{

	exitButtonRect = { 809, 80, 891, 115 };
	exitCheck = false;

	giveupButton = { 654, 533, 738, 561 };

	removeBoardButton = { 560,533,644,561 };

	POINT pos;
	pos.x = 260;
	pos.y = 533;
	for (int i = 0; i < COLOR_END; ++i) {
		ColorButton* cButton = new ColorButton();
		if (i == WHITE)
			cButton->rect = { pos.x + (i * 32), pos.y, pos.x + 28 + (i * 35), pos.y + 24 };
		else
			cButton->rect = { pos.x + (i * 32), pos.y, pos.x + 28 + (i * 32), pos.y + 24 };
		cButton->color = BLACK + i;
		colorButton.push_back(cButton);
	}

}

void InGameScene::setCheckButton(bool check) {
	exitCheck = false;
}
void InGameScene::renderScene(HDC hdc)
{
	back->render(hdc,0,0);
	Question::getInstance()->renderQuestion(hdc);
	
	PlayerManager::getInstance()->renderPlayer(hdc);
	BrushManager::getInstance()->renderBrush(hdc);

	ScoreManager::getInstance()->renderScore(hdc);
}
void InGameScene::checkPushRemoveButton() {
	if (!BrushManager::getInstance()->checkMyTurn())
		return;
	if (InputManager::getInstance()->checkLButton() ) {
		RECT temp;
		if (IntersectRect(&temp, &removeBoardButton, &InputManager::getInstance()->getlButtonRect())) {
			PacketManager::getInstance()->removeBoardPkt();
		}
	}
}
void InGameScene::checkPushGiveupButton() {
	if (!BrushManager::getInstance()->checkMyTurn())
		return;
	if (InputManager::getInstance()->checkLButton() ) {
		RECT temp;
		if (IntersectRect(&temp, &giveupButton, &InputManager::getInstance()->getlButtonRect())) {
			PacketManager::getInstance()->giveupTurnPkt();
			BrushManager::getInstance()->changeMyTurn(false);
		}
	}
}
void InGameScene::checkPushColorButton() {
	if (!BrushManager::getInstance()->checkMyTurn())
		return;
	if (InputManager::getInstance()->checkLButton()) {
		RECT temp;
		for (auto &iter : colorButton) {
			if (IntersectRect(&temp, &iter->rect, &InputManager::getInstance()->getlButtonRect())) {
				PacketManager::getInstance()->changeColorPkt((Color)iter->color);
			}
		}
	}
}
void InGameScene::checkPushExitButton()
{
	if (InputManager::getInstance()->checkLButton() && exitCheck == false) {
		RECT temp;
		if (IntersectRect(&temp, &exitButtonRect, &InputManager::getInstance()->getlButtonRect())) {
			PacketManager::getInstance()->exitRoomPkt();
			PlayerManager::getInstance()->exitPlayer();
			BrushManager::getInstance()->removeBoard();
			exitCheck = true;
		}
	}
}
void InGameScene::releaseButton() {
	for (auto &iter : colorButton)
		delete iter;
	colorButton.clear();
}
void InGameScene::releaseScene()
{
	
	releaseButton();
	ScoreManager::getInstance()->releaseScore();
	ScoreManager::getInstance()->releaseInstance();
	Question::getInstance()->releaseInstance();
	BrushManager::getInstance()->releaseInstance();
	PlayerManager::getInstance()->releasePlayer();
	PlayerManager::getInstance()->releaseInstance();
}