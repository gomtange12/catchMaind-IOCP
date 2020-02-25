#pragma once
#include "Singleton.h"
#include "BrushManager.h"
struct Brush;
class PacketManager : public Singleton<PacketManager>
{
private:
	SOCKET  sock;
	WSABUF	sendWsabuf;
	char 	sendBuffer[BUFSIZE];
public:
	void	initPacketManager(SOCKET & _sock);
	void	sendPkt();
	void	sendLobbyChatPkt(string& str);
	void	sendInGameChatPkt(string & str);
	void	LoginPkt(string & id, string & pw);
	void	makeNewRoomPkt();
	void	joinRoomPkt(int rNum);
	void	drawBrushPkt(Brush brush);
	void	changeColorPkt(Color color);
	void	removeBoardPkt();
	void	exitRoomPkt();
	void	giveupTurnPkt();
};

