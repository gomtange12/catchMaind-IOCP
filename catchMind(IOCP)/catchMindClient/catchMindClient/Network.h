#pragma once
#include "Singleton.h"
#define MAX_MATCH_USER 2


class Network :public Singleton<Network>
{
private:
	SOCKET			sock;
	unsigned int	myId;
	string			nickName;
	bool			login;

	list<int>		otherIds;
	map<int,string>	otherNickName;
	vector<int>		matchId;

private:
	WSABUF			recvWsabuf;
	char			recvBuffer[BUFSIZE];
	unsigned char	packetBuffer[BUFSIZE];
	DWORD			inPacketSize = 0;
	int				savedPacketSize = 0;
public:

	void			initNetwork(HWND hWnd);
	void			processSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void			readPacket();
	void			processPacket(unsigned char* ptr);
	void			resetMatchId();
	void			releaseNetwork();

public:
	void			processConnect(unsigned char* ptr);
	void			processLoginSuccessfulAndNickname(unsigned char* ptr);
	void			processChangeScene(unsigned char* ptr);
	void			processMakeNewRoom(unsigned char* ptr);
	void			processJoinUserRoom(unsigned char* ptr);
	void			processMatchRoom(unsigned char* ptr);
	void			processChangeNextTurn(unsigned char* ptr);
	void			processDrawBoard(unsigned char* ptr);
	void			processChangeColor(unsigned char* ptr);
	void			processRemoveBoard(unsigned char* ptr);
	void			processExitRoom(unsigned char* ptr);
	void			processRemoveRoom(unsigned char* ptr);
	void			processLobbyChat(unsigned char* ptr);
	void			processInGameChat(unsigned char* ptr);
	void			processQuestionInfo(unsigned char* ptr);
	void			processDisconnectUser(unsigned char* ptr);
	void			processUserGetScore(unsigned char* ptr);


};

