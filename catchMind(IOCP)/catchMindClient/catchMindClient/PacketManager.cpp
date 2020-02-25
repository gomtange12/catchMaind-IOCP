#include "stdafx.h"
#include "PacketManager.h"
#include "../../Common/Protocol.h"

void PacketManager::initPacketManager(SOCKET& _sock) {
	sock = _sock;
	sendWsabuf.buf = sendBuffer;
	sendWsabuf.len = BUFSIZE;
}
void PacketManager::sendPkt()
{
	DWORD iobyte;
	int ret = WSASend(sock, &sendWsabuf, 1, &iobyte, 0, NULL, NULL);
	if (ret) {
		int error_code = WSAGetLastError();
		printf("Error while sending SendPacket [%d]", error_code);
	}

}

void PacketManager::sendLobbyChatPkt(string& str)
{
	CS_PAKET_CHAT_LOBBY *pkt = reinterpret_cast<CS_PAKET_CHAT_LOBBY *>(sendBuffer);
	pkt->len = (char)str.length();
	pkt->size = (BYTE)sizeof(CS_PAKET_CHAT_LOBBY) +pkt->len;
	sendWsabuf.len = pkt->size;
	strcpy_s(pkt->chat, str.c_str());
	pkt->type = CS_PACKET_INDEX_CHAT_LOBBY;
	sendPkt();
}
void PacketManager::sendInGameChatPkt(string& str)
{
	CS_PAKET_CHAT_INGAME *pkt = reinterpret_cast<CS_PAKET_CHAT_INGAME *>(sendBuffer);
	pkt->len = (char)str.length();
	pkt->size = (BYTE)sizeof(CS_PAKET_CHAT_INGAME) + pkt->len;
	sendWsabuf.len = pkt->size;
	strcpy_s(pkt->chat, str.c_str());
	pkt->type = CS_PACKET_INDEX_CHAT_INGAME;
	sendPkt();
}
void PacketManager::LoginPkt(string& id, string& pw)
{
	
	CS_PAKET_LOGIN_INFO *pkt = reinterpret_cast<CS_PAKET_LOGIN_INFO *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_LOGIN_INFO);
	sendWsabuf.len = pkt->size;
	strcpy(pkt->id, id.c_str());
	strcpy(pkt->pw, pw.c_str());	
	pkt->type = CS_PACKET_INDEX_LOGIN_INFO;
	sendPkt();

}
void PacketManager::makeNewRoomPkt()
{
	CS_PAKET_NEW_ROOM *pkt = reinterpret_cast<CS_PAKET_NEW_ROOM *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_NEW_ROOM);
	sendWsabuf.len = pkt->size;
	pkt->type = CS_PACKET_INDEX_MAKE_ROOM;
	sendPkt();
	
}
void PacketManager::joinRoomPkt(int rNum)
{
	CS_PAKET_JOIN_ROOM *pkt = reinterpret_cast<CS_PAKET_JOIN_ROOM *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_JOIN_ROOM);
	sendWsabuf.len = pkt->size;
	pkt->rNum = rNum;
	pkt->type = CS_PACKET_INDEX_JOIN_ROOM;
	sendPkt();
}
void PacketManager::drawBrushPkt(Brush brs) 
{
	CS_PAKET_DRAW_BOARD *pkt = reinterpret_cast<CS_PAKET_DRAW_BOARD *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_DRAW_BOARD);
	sendWsabuf.len = pkt->size;
	pkt->posX = (WORD)brs.pos.x;
	pkt->posY = (WORD)brs.pos.y;
	pkt->oldPosX = (WORD)brs.oldPos.x;
	pkt->oldPosY = (WORD)brs.oldPos.y;
	pkt->type = CS_PACKET_INDEX_DRAW_BOARD;
	sendPkt();
}

void PacketManager::changeColorPkt(Color color)
{
	CS_PAKET_CHANGE_COLOR *pkt = reinterpret_cast<CS_PAKET_CHANGE_COLOR *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_CHANGE_COLOR);
	sendWsabuf.len = pkt->size;
	pkt->color = color;
	pkt->type = CS_PACKET_INDEX_CHANGE_COLOR;
	sendPkt();
}
void PacketManager::removeBoardPkt()
{
	CS_PAKET_REMOVE_BOARD *pkt = reinterpret_cast<CS_PAKET_REMOVE_BOARD *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_REMOVE_BOARD);
	sendWsabuf.len = pkt->size;
	pkt->type = CS_PACKET_INDEX_REMOVE_BOARD;
	sendPkt();
}

void PacketManager::exitRoomPkt()
{
	CS_PAKET_EXIT_ROOM *pkt = reinterpret_cast<CS_PAKET_EXIT_ROOM *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_EXIT_ROOM);
	sendWsabuf.len = pkt->size;
	pkt->type = CS_PACKET_INDEX_EXIT_ROOM;
	sendPkt();
}
void PacketManager::giveupTurnPkt()
{
	CS_PAKET_GIVEUP_TURN *pkt = reinterpret_cast<CS_PAKET_GIVEUP_TURN *>(sendBuffer);
	pkt->size = sizeof(CS_PAKET_GIVEUP_TURN);
	sendWsabuf.len = pkt->size;
	pkt->type = CS_PACKET_INDEX_GIVEUP_TURN;
	sendPkt();
}