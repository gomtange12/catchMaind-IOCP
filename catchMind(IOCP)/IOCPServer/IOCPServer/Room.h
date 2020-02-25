#pragma once
#define MAX_JOIN_USER 2

class Room
{
private:
	std::vector<int>	joinUserId;
	std::vector<int>	saveScore;
	std::vector<Brush*> saveBrush;
	std::string			roomQuestion;

	Color				saveColor;

	int					roomUserCount;
	int					roomNum;
	int					turnNum;
public:
	bool				match;
	bool				beMade;
public:
	void				initRoom(int rNum);
	bool				findVacancy(int id);
	void				joinRoom(int id);
	void				informQuestion();
	void				changeTurnRoom();
	void				changeNextTurn();
	void				exitRoom(int id);
	bool				checkObserver(int id);
	void				checkRemoveRoom(int id);
	void				informJoinRoomUsers(int id, bool observer);
	bool				checkInUser(int id);
	void				changeColor(Color _color);
	void				drawInformInUser(int id, Brush brs);
	void				sendSaveBrushJoinObserver(int id);
	void				sendSaveScoreJoinObserver(int id);
	void				removeBoard();
	void				sendChatJoinRoomUser(int id, std::string chat);
	bool				checkForCorrectAnswers(int id, std::string chat);
	void				releaseRoom();
	int					getTurnNum() { return turnNum; };
};

