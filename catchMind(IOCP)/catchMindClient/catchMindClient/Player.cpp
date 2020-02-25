#include "stdafx.h"
#include "Player.h"
#include "BitMap.h"
#include "ResManager.h"
void Player::init()
{
	banner = ResManager::getInstance()->getIngameBitMap(INGAME_RES_TURN);
	nickName = "Unknown";
	joinNum = -1;
	turn = false;
	position.x = -200;
	position.y = -200;
}

void Player::update()
{

}
void Player::setPosition(int jNum) 
{
	joinNum = jNum;
	if (joinNum <= 4)
		position.x = 38;
	else
		position.x = 790;

	if (joinNum == 1 || joinNum == 5)
		position.y = 179;
	if(joinNum == 2 || joinNum == 6)
		position.y = 286;
	if(joinNum == 3 || joinNum == 7)
		position.y = 394;
	if(joinNum == 4 || joinNum == 8)
		position.y = 501;

	if(joinNum == -1 || joinNum > 8){
		position.x = -200;
		position.y = -200;
	}
}
void Player::render(HDC hdc)
{
	if (turn == true && joinNum != -1) 
		banner->render(hdc, (float)position.x, (float)position.y+2);
	
	TextOut(hdc, position.x + 9, position.y + 26, nickName.c_str(), (int)nickName.length());
}
