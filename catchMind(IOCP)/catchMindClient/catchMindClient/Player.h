#pragma once


class BitMap;
class Player
{
private:
protected:
	string		nickName;
	BitMap*		banner;
	POINT		position;
	int			joinNum;
	bool		turn;
public:

public:
	virtual void	init();
	virtual void	update();
	virtual void	setPosition(int joinNum);
	virtual void	render(HDC hdc);

	virtual void	setNickName(string nick) { nickName = nick;};
	virtual string	getNickName()const { return nickName; };
	virtual int		getJoinNum()const { return joinNum; };
	virtual void	chageTurn(bool _turn) { turn = _turn; };
};

class OtherPlayer :public Player 
{
private:
public:
};