#include "stdafx.h"
#include "Network.h"
#include "../../Common/Protocol.h"
#include "PacketManager.h"
#include "SceneManager.h"
#include "ChatManager.h"
#include "Lobby.h"
#include "Login.h"
#include <fstream>
#include "VisitorList.h"
#include "RoomManager.h"
#include "PlayerManager.h"
#include "BrushManager.h"
#include "Question.h"
#include "ScoreManager.h"

void Network::initNetwork(HWND hWnd)
{
	myId = -1;
	login = false;
	resetMatchId();
	
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return;

	sock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);
	if (sock == INVALID_SOCKET)
	{
		cout << "err on socket" << endl;
		return;
	}

	//네이글알고리즘
	//char opt = TRUE;
	//setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));

	string ip;
	ifstream in("ipconfig.txt");
	while (!in.eof()) {
		in >> ip;
	}

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = inet_addr(ip.c_str());
	int retval = WSAConnect(sock, (sockaddr*)&serveraddr, sizeof(serveraddr),NULL, NULL, NULL, NULL);
	if (retval == SOCKET_ERROR)
	{
		cout << "err on connect" << endl;
		return;
	}

	retval = WSAAsyncSelect(sock, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (retval == SOCKET_ERROR)
		return;
	

	recvWsabuf.buf = recvBuffer;
	recvWsabuf.len = BUFSIZE;

	PacketManager::getInstance()->initPacketManager(sock);
	return;
}

void Network::processSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int addrlen = 0;
	int retval = 0;


	if (WSAGETSELECTERROR(lParam))
	{
		int err_code = WSAGETSELECTERROR(lParam);
		return;
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
	{
		readPacket();
		break;
	}
	case FD_CLOSE:
		closesocket(wParam);
		exit(1);
		break;
	}
}
void Network::readPacket()
{
	DWORD iobyte, ioflag = 0;

	int ret = WSARecv(sock, &recvWsabuf, 1, &iobyte, &ioflag, NULL, NULL);
	if (ret) {
		int err_code = WSAGetLastError();
		printf("Recv Error [%d]\n", err_code);
	}

	BYTE *ptr = reinterpret_cast<BYTE *>(recvBuffer);

	while (0 != iobyte) {
		if (0 == inPacketSize) 
			inPacketSize = ptr[0];
		if (iobyte + savedPacketSize >= inPacketSize)
		{
			memcpy(packetBuffer + savedPacketSize, ptr, inPacketSize - savedPacketSize);
			////
			processPacket(packetBuffer);
			////
			ptr += inPacketSize - savedPacketSize;
			iobyte -= inPacketSize - savedPacketSize;
			inPacketSize = 0;
			savedPacketSize = 0;
		}
		else {
			memcpy(packetBuffer + savedPacketSize, ptr, iobyte);
			savedPacketSize += iobyte;
			iobyte = 0;
		}
	}
}
void Network::processPacket(unsigned char* ptr) 
{
	switch (ptr[1])
	{
		case SC_PACKET_INDEX_CONNECT_RET:
		{
			processConnect(ptr);	
			break;
		}
		case SC_PACKET_INDEX_LOGIN_RET:
		{
			processLoginSuccessfulAndNickname(ptr);	
			break;
		}
		case SC_PACKET_INDEX_SCENE:
		{
			processChangeScene(ptr);
			break;
		}
		case SC_PACKET_INDEX_NEW_ROOM:
		{
			processMakeNewRoom(ptr);
			break;
		}
		case SC_PACKET_INDEX_JOIN_ROOM:
		{
			processJoinUserRoom(ptr);
			
			break;
		}
		case SC_PACKET_INDEX_MATCH_ROOM:
		{
			processMatchRoom(ptr);
			break;
		}
		case SC_PACKET_INDEX_CHANGE_TURN:
		{
			processChangeNextTurn(ptr);
			break;
		}
		case SC_PACKET_INDEX_DRAW_BOARD:
		{
			processDrawBoard(ptr);
			break;
		}
		case SC_PACKET_INDEX_CHANGE_COLOR:
		{
			processChangeColor(ptr);
			break;
		}
		case SC_PACKET_INDEX_REMOVE_BOARD:
		{
			processRemoveBoard(ptr);
			break;
		}
		case SC_PACKET_INDEX_EXIT_ROOM:
		{
			processExitRoom(ptr);
			break;
		}
		case SC_PACKET_INDEX_REMOVE_ROOM:
		{
			processRemoveRoom(ptr);
			break;
		}
		case SC_PACKET_INDEX_CHAT_LOBBY:
		{
			processLobbyChat(ptr);
			break;
		}
		case SC_PACKET_INDEX_CHAT_INGAME:
		{
			processInGameChat(ptr);
			break;
		}
		case SC_PACKET_INDEX_QUEST_INFO:
		{
			processQuestionInfo(ptr);
			break;
		}

		case SC_PACKET_INDEX_DISCONNECT_RET:
		{
			processDisconnectUser(ptr);
			break;
		}
		case SC_PACKET_INDEX_GET_SCORE:
		{
			processUserGetScore(ptr);
			break;
		}

	}
}
void Network::resetMatchId() {
	matchId.clear();
	for (int i = 0; i < MAX_MATCH_USER; ++i)
		matchId.push_back(-1);
}
void Network::releaseNetwork()
{
	PacketManager::getInstance()->releaseInstance();
	closesocket(sock);
	WSACleanup();
}

void Network::processConnect(unsigned char* ptr)
{
	SC_PAKET_CONNECT_RET *pkt = reinterpret_cast<SC_PAKET_CONNECT_RET *>(ptr);

	if (myId == -1) {
		myId = pkt->id;
	}
	else if (myId != pkt->id) {
		otherIds.push_back(pkt->id);
	}
}

void Network::processLoginSuccessfulAndNickname(unsigned char* ptr)
{
	SC_PAKET_LOGIN_RET *pkt = reinterpret_cast<SC_PAKET_LOGIN_RET *>(ptr);
	if (myId == pkt->id && login == false) {
		nickName.clear();
		for (int i = 0; i < pkt->nickLen; ++i) {
			nickName.push_back(pkt->nick[i]);
		}

		ChatManager::getInstance()->setMyNickName(nickName);
		VisitorList::getInstance()->setMyNick(nickName);
		PlayerManager::getInstance()->setMyNick(nickName);
		Login::getInstance()->hideLoginWindow();
		login = true;
	}
	if (myId != pkt->id) {
		string nick;
		for (int i = 0; i < pkt->nickLen; ++i) {
			nick.push_back(pkt->nick[i]);
		}
		otherNickName.insert(make_pair(pkt->id, nick));
		VisitorList::getInstance()->setOtherId(nick);

	}
}

void Network::processChangeScene(unsigned char* ptr)
{
	SC_PAKET_SCENE *pkt = reinterpret_cast<SC_PAKET_SCENE *>(ptr);
	SceneManager::getInstance()->changScene((SCENE_NUM)pkt->sceneNum);
	if ((SCENE_NUM)pkt->sceneNum == SCENE_LOBBY) {
		VisitorList::getInstance()->setSceneNum(SCENE_LOBBY);
		SceneManager::getInstance()->setCheckButton(false);
		RoomManager::getInstance()->exitMatch();
		BrushManager::getInstance()->changeMyTurn(false);
		Question::getInstance()->removeQuestion();
		resetMatchId();

	}
	if ((SCENE_NUM)pkt->sceneNum == SCENE_GAME)
		BrushManager::getInstance()->removeBoard();
}

void Network::processMakeNewRoom(unsigned char* ptr)
{
	SC_PAKET_NEW_ROOM *pkt = reinterpret_cast<SC_PAKET_NEW_ROOM *>(ptr);
	RoomManager::getInstance()->makeNewRoom(pkt->roomNum);
}

void Network::processJoinUserRoom(unsigned char* ptr)
{
	SC_PAKET_JOIN_ROOM *pkt = reinterpret_cast<SC_PAKET_JOIN_ROOM *>(ptr);
	for (auto &iter : matchId) {
		if (iter == pkt->joinId)
			break;
	}
	for (auto &iter : matchId) {
		if (iter == -1) {
			iter = pkt->joinId;
			if (myId == pkt->joinId) {
				PlayerManager::getInstance()->joinPlayer(nickName);
				break;
			}
			else {
				PlayerManager::getInstance()->joinPlayer(otherNickName.find(pkt->joinId)->second);
				break;
			}
		}
	}
}

void Network::processMatchRoom(unsigned char* ptr)
{
	RoomManager::getInstance()->matchRoom();
}

void Network::processChangeNextTurn(unsigned char* ptr)
{
	SC_PAKET_CHANGE_TURN *pkt = reinterpret_cast<SC_PAKET_CHANGE_TURN *>(ptr);
	BrushManager::getInstance()->removeBoard();
	Question::getInstance()->removeQuestion();
	BrushManager::getInstance()->changeMyTurn(false);
	PlayerManager::getInstance()->changeTurn(pkt->num);
	if (PlayerManager::getInstance()->myTurnId == pkt->num)
		BrushManager::getInstance()->changeMyTurn(true);
}

void Network::processDrawBoard(unsigned char* ptr)
{
	SC_PAKET_DRAW_BOARD *pkt = reinterpret_cast<SC_PAKET_DRAW_BOARD *>(ptr);
	Brush brush;
	brush.pos.x = pkt->posX;
	brush.pos.y = pkt->posY;
	brush.oldPos.x = pkt->oldPosX;
	brush.oldPos.y = pkt->oldPosY;
	BrushManager::getInstance()->saveBrushPosition(brush);
}

void Network::processChangeColor(unsigned char* ptr)
{
	SC_PAKET_CHANGE_COLOR *pkt = reinterpret_cast<SC_PAKET_CHANGE_COLOR *>(ptr);
	BrushManager::getInstance()->color = (Color)pkt->color;
}

void Network::processRemoveBoard(unsigned char* ptr)
{
	BrushManager::getInstance()->removeBoard();
}

void Network::processExitRoom(unsigned char* ptr)
{
	SC_PAKET_EXIT_ROOM *pkt = reinterpret_cast<SC_PAKET_EXIT_ROOM *>(ptr);
	for (auto &iter : matchId) {
		if (iter == (int)pkt->id)
			iter = -1;
	}
	PlayerManager::getInstance()->exitOtherPlayer(otherNickName.find(pkt->id)->second);
	BrushManager::getInstance()->changeMyTurn(false);
	Question::getInstance()->removeQuestion();
}

void Network::processRemoveRoom(unsigned char* ptr)
{
	SC_PAKET_REMOVE_ROOM *pkt = reinterpret_cast<SC_PAKET_REMOVE_ROOM *>(ptr);
	RoomManager::getInstance()->removeRoom(pkt->roomNum);
}

void Network::processLobbyChat(unsigned char* ptr)
{
	SC_PAKET_CHAT_LOBBY *pkt = reinterpret_cast<SC_PAKET_CHAT_LOBBY *>(ptr);
	string chat;
	for (int i = 0; i < pkt->len; ++i) {
		chat.push_back(pkt->chat[i]);
	}

	ChatManager::getInstance()->recvChat(chat);
}

void Network::processInGameChat(unsigned char* ptr)
{
	SC_PAKET_CHAT_INGAME *pkt = reinterpret_cast<SC_PAKET_CHAT_INGAME *>(ptr);
	string chat;
	for (int i = 0; i < pkt->len; ++i) {
		chat.push_back(pkt->chat[i]);
	}
	int i = 1, num = 0;
	for (auto &iter : matchId) {
		if (iter == (int)pkt->id)
			num = i;
		else
			i++;
	}
	ChatManager::getInstance()->setInGameChatBalloonPosition(num);
	ChatManager::getInstance()->recvChat(chat);
}

void Network::processQuestionInfo(unsigned char* ptr)
{
	SC_PAKET_QUEST_INFO *pkt = reinterpret_cast<SC_PAKET_QUEST_INFO *>(ptr);
	string question;
	for (int i = 0; i < pkt->len; ++i)
		question.push_back(pkt->question[i]);
	Question::getInstance()->changeQuestion(question);
}

void Network::processDisconnectUser(unsigned char* ptr)
{
	SC_PAKET_DISCONNECT_RET *pkt = reinterpret_cast<SC_PAKET_DISCONNECT_RET *>(ptr);

	for (auto &iter : matchId) {
		if (iter == (int)pkt->id)
			iter = -1;
	}
	if (otherNickName.size() > 0) {
		VisitorList::getInstance()->disconnetId(otherNickName.find(pkt->id)->second);
		PlayerManager::getInstance()->exitOtherPlayer(otherNickName.find(pkt->id)->second);
		otherNickName.erase(pkt->id);
	}

	for (auto iter = otherIds.begin(); iter != otherIds.end();) {
		if ((*iter) == (int)pkt->id)
			iter = otherIds.erase(iter);
		else
			++iter;
	}
}

void Network::processUserGetScore(unsigned char* ptr)
{
	SC_PAKET_GET_SCORE *pkt = reinterpret_cast<SC_PAKET_GET_SCORE *>(ptr);
	int i = 0, num = 0;
	for (auto &iter : matchId) {
		if (iter == (int)pkt->id)
			num = i;
		else
			i++;
	}
	ScoreManager::getInstance()->setScorePosition(num);
	ScoreManager::getInstance()->getScore(num);
}
