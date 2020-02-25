#pragma once
#include "Singleton.h"
struct PlayerScore
{
	int point;
	POINT pos;
};
class ScoreManager :public Singleton<ScoreManager>
{
private:
	vector<PlayerScore*> playerScore;
	
public:
	void		initScore();
	void		setScorePosition(int num);
	void		getScore(int num);
	void		renderScore(HDC hdc);
	void		releaseScore();
};

