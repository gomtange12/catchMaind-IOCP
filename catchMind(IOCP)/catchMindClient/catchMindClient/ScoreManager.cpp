#include "stdafx.h"
#include "ScoreManager.h"

void ScoreManager::initScore()
{
	for (int i = 0; i < 8; ++i) {
		PlayerScore* nPlayerScore = new PlayerScore();
		nPlayerScore->point = 0;
		playerScore.push_back(nPlayerScore);
		setScorePosition(i);
	}
}

void ScoreManager::setScorePosition(int num)
{
	POINT tempPos;
	if (num <= 3)
		tempPos.x = 74;
	if (num >= 4)
		tempPos.x = 911;

	if (num == 0 || num == 4)
		tempPos.y = 254;
	if (num == 1 || num == 5)
		tempPos.y = 360;
	if (num == 2 || num == 6)
		tempPos.y = 468;
	if (num == 3 || num == 7)
		tempPos.y = 575;

	playerScore[num]->pos = tempPos;
}

void ScoreManager::getScore(int num)
{
	playerScore[num]->point += 1;
}

void ScoreManager::renderScore(HDC hdc)
{
	SetTextColor(hdc, RGB(0, 0, 0));

	string point;
	for (auto &iter : playerScore) {
		point= to_string(iter->point);
		TextOut(hdc, iter->pos.x, iter->pos.y, point.c_str(), (int)point.length());
	}
}

void ScoreManager::releaseScore()
{
	for (auto &iter : playerScore)
		delete iter;
	playerScore.clear();
}
