#include "pch.h"
#include "Define.h"
#include "PacketManager.h"
#include "PlayerManager.h"

void PacketManager::sendPacket(int id, void* packet)
{
	OverData *over = new OverData;
	memcpy(over->iocpBuf, packet, reinterpret_cast<unsigned char*>(packet)[0]);
	over->todo = OP_SEND;
	over->wsaBuf.buf = (char *)over->iocpBuf;
	over->wsaBuf.len = over->iocpBuf[0];
	ZeroMemory(&over->wsaOver, sizeof(WSAOVERLAPPED));

	int ret = WSASend(PlayerManager::getInstance()->getPlayerSock(id), &over->wsaBuf, 1, NULL, 0, &over->wsaOver, 0);
	if (0 != ret) {
		int err_no = WSAGetLastError();
		if (WSA_IO_PENDING != err_no)
			printf("¿À·ù");
	}
	
};
void PacketManager::connectPacket(int id) 
{
	SC_PAKET_CONNECT_RET pkt;
	pkt.id = id;
	pkt.type = SC_PACKET_INDEX_CONNECT_RET;
	pkt.size = sizeof(SC_PAKET_CONNECT_RET);
	sendPacket(id, &pkt);
	
	
}
void PacketManager::loginSuccessfulAndNicknamePacket(int id, int sendId, std::string nick)
{
	SC_PAKET_LOGIN_RET pkt;
	pkt.id = id;
	pkt.nickLen = (char)nick.size();
	strcpy_s(pkt.nick, nick.c_str());
	pkt.type = SC_PACKET_INDEX_LOGIN_RET;
	pkt.size = sizeof(SC_PAKET_LOGIN_RET) + pkt.nickLen;
	sendPacket(sendId, &pkt);

}

void PacketManager::sendLobbyChatPacket(int id,std::string chat)
{
	SC_PAKET_CHAT_LOBBY pkt;
	pkt.len = (char)chat.length();
	strcpy_s(pkt.chat, chat.c_str());
	pkt.type = SC_PACKET_INDEX_CHAT_LOBBY;
	pkt.size = (BYTE)sizeof(SC_PAKET_CHAT_LOBBY) + pkt.len;
	sendPacket(id, &pkt);
}
void PacketManager::sendInGameChatPacket(int id, int sendId,std::string chat)
{
	SC_PAKET_CHAT_INGAME pkt;
	pkt.id = id;
	pkt.len = (char)chat.length();
	strcpy_s(pkt.chat, chat.c_str());
	pkt.type = SC_PACKET_INDEX_CHAT_INGAME;
	pkt.size = (BYTE)sizeof(SC_PAKET_CHAT_INGAME) + pkt.len;
	sendPacket(sendId, &pkt);
}
void PacketManager::changeScenePacket(int id, int sNum) {
	SC_PAKET_SCENE pkt;
	pkt.sceneNum = sNum;
	pkt.size = sizeof(SC_PAKET_SCENE);
	pkt.type = SC_PACKET_INDEX_SCENE;
	sendPacket(id, &pkt);
	
}
void PacketManager::makeNewRoomPacket(int id, int rNum) {
	SC_PAKET_NEW_ROOM pkt;
	pkt.roomNum = rNum;
	pkt.size = sizeof(SC_PAKET_NEW_ROOM);
	pkt.type = SC_PACKET_INDEX_NEW_ROOM;
	sendPacket(id, &pkt);
	
}
void PacketManager::informJoinUserPacket(int id, int otherId) {
	SC_PAKET_JOIN_ROOM pkt;
	pkt.joinId = otherId;
	pkt.size = sizeof(SC_PAKET_JOIN_ROOM);
	pkt.type = SC_PACKET_INDEX_JOIN_ROOM;
	sendPacket(id, &pkt);
}
void PacketManager::informMatchPacket(int id) {
	SC_PAKET_MATCH_ROOM pkt;
	pkt.size = sizeof(SC_PAKET_MATCH_ROOM);
	pkt.type = SC_PACKET_INDEX_MATCH_ROOM;
	sendPacket(id, &pkt);
}
void PacketManager::changeNextTurnPacket(int id, int num)
{
	SC_PAKET_CHANGE_TURN pkt;
	pkt.num = num;
	pkt.size = sizeof(SC_PAKET_CHANGE_TURN);
	pkt.type = SC_PACKET_INDEX_CHANGE_TURN;
	sendPacket(id, &pkt);
}
void PacketManager::drawInformInRoomUserPacket(int id, Brush brush)
{
	SC_PAKET_DRAW_BOARD pkt;
	pkt.size = sizeof(SC_PAKET_DRAW_BOARD);
	pkt.type = SC_PACKET_INDEX_DRAW_BOARD;
	pkt.posX = (WORD)brush.pos.x;
	pkt.posY = (WORD)brush.pos.y;
	pkt.oldPosX = (WORD)brush.oldPos.x;
	pkt.oldPosY = (WORD)brush.oldPos.y;
	sendPacket(id, &pkt);

}
void PacketManager::changeColorPacket(int id, Color color) {
	SC_PAKET_CHANGE_COLOR pkt;
	pkt.color = color;
	pkt.type = SC_PACKET_INDEX_CHANGE_COLOR;
	pkt.size = sizeof(SC_PAKET_CHANGE_COLOR);
	sendPacket(id, &pkt);
}
void PacketManager::exitRoomPacket(int id, int sendId)
{
	SC_PAKET_EXIT_ROOM pkt;
	pkt.id = id;
	pkt.type = SC_PACKET_INDEX_EXIT_ROOM;
	pkt.size = sizeof(SC_PAKET_EXIT_ROOM);
	sendPacket(sendId, &pkt);
}
void PacketManager::removeBoardPacket(int id)
{
	SC_PAKET_REMOVE_BOARD pkt;
	pkt.type = SC_PACKET_INDEX_REMOVE_BOARD;
	pkt.size = sizeof(SC_PAKET_REMOVE_BOARD);
	sendPacket(id, &pkt);
}
void PacketManager::removeRoomPacket(int id,int roomNum) {
	SC_PAKET_REMOVE_ROOM pkt;
	pkt.roomNum = roomNum;
	pkt.type = SC_PACKET_INDEX_REMOVE_ROOM;
	pkt.size = sizeof(SC_PAKET_REMOVE_ROOM);
	sendPacket(id, &pkt);
}
void PacketManager::infromQuestionInfoPacket(int id, std::string question)
{
	SC_PAKET_QUEST_INFO pkt;
	pkt.len = (char)question.length();
	strcpy_s(pkt.question, question.c_str());
	pkt.size = (BYTE)sizeof(SC_PAKET_QUEST_INFO)+ pkt.len;
	pkt.type = SC_PACKET_INDEX_QUEST_INFO;
	sendPacket(id, &pkt);
}

void PacketManager::infromUsersGetScorePacket(int id,int sendId)
{
	SC_PAKET_GET_SCORE pkt;
	pkt.id = id;
	pkt.size = sizeof(SC_PAKET_GET_SCORE);
	pkt.type = SC_PACKET_INDEX_GET_SCORE;
	sendPacket(sendId, &pkt);
}
void PacketManager::disconnectClientPacket(int id,int sendId)
{
	SC_PAKET_DISCONNECT_RET pkt;
	pkt.id = id;
	pkt.size = sizeof(SC_PAKET_DISCONNECT_RET);
	pkt.type = SC_PACKET_INDEX_DISCONNECT_RET;
	sendPacket(sendId, &pkt);
}

