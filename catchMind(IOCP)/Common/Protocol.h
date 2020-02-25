#pragma once
enum Color
{
	BLACK,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	WHITE,
	COLOR_END
};

enum SC_PACKET_INDEX
{
	SC_PACKET_INDEX_CONNECT_RET = 1,
	SC_PACKET_INDEX_LOGIN_RET,
	SC_PACKET_INDEX_SCENE,
	SC_PACKET_INDEX_NEW_ROOM,
	SC_PACKET_INDEX_JOIN_ROOM,
	SC_PACKET_INDEX_MATCH_ROOM,
	SC_PACKET_INDEX_CHANGE_TURN,
	SC_PACKET_INDEX_DRAW_BOARD,
	SC_PACKET_INDEX_CHANGE_COLOR,
	SC_PACKET_INDEX_REMOVE_BOARD,
	SC_PACKET_INDEX_EXIT_ROOM,
	SC_PACKET_INDEX_REMOVE_ROOM,
	SC_PACKET_INDEX_CHAT_LOBBY,
	SC_PACKET_INDEX_CHAT_INGAME,
	SC_PACKET_INDEX_QUEST_INFO,
	SC_PACKET_INDEX_DISCONNECT_RET,
	SC_PACKET_INDEX_GET_SCORE,
	SC_PACKET_END
};
enum CS_PACKET_INDEX
{
	CS_PACKET_INDEX_ = SC_PACKET_END,
	CS_PACKET_INDEX_CHAT_LOBBY,
	CS_PACKET_INDEX_CHAT_INGAME,
	CS_PACKET_INDEX_LOGIN_INFO,
	CS_PACKET_INDEX_MAKE_ROOM,
	CS_PACKET_INDEX_JOIN_ROOM,
	CS_PACKET_INDEX_DRAW_BOARD,
	CS_PACKET_INDEX_CHANGE_COLOR,
	CS_PACKET_INDEX_REMOVE_BOARD,
	CS_PACKET_INDEX_EXIT_ROOM,
	CS_PACKET_INDEX_GIVEUP_TURN

};
#pragma pack(1)
//================Server===================//

struct SC_PAKET_CONNECT_RET {
	BYTE size;
	BYTE type;
	char id;
};
struct SC_PAKET_LOGIN_RET {
	BYTE size;
	BYTE type;
	char nickLen;
	char nick[128];
	char id;
};
struct SC_PAKET_SCENE {
	BYTE size;
	BYTE type;
	char sceneNum;
};
struct SC_PAKET_NEW_ROOM {
	BYTE size;
	BYTE type;
	char roomNum;
};struct SC_PAKET_JOIN_ROOM {
	BYTE size;
	BYTE type;
	char joinId;
};
struct SC_PAKET_MATCH_ROOM {
	BYTE size;
	BYTE type;
};
struct SC_PAKET_CHANGE_TURN {
	BYTE size;
	BYTE type;
	char num;
};
struct SC_PAKET_DRAW_BOARD
{
	BYTE size;
	BYTE type;
	WORD posX;
	WORD posY;
	WORD oldPosX;
	WORD oldPosY;

};
struct SC_PAKET_CHANGE_COLOR {
	BYTE size;
	BYTE type;
	WORD color;
};
struct SC_PAKET_REMOVE_BOARD {
	BYTE size;
	BYTE type;
};
struct SC_PAKET_EXIT_ROOM {
	BYTE size;
	BYTE type;
	char id;
}; 
struct SC_PAKET_REMOVE_ROOM {
	BYTE size;
	BYTE type;
	char roomNum;
};
struct SC_PAKET_CHAT_LOBBY {
	BYTE size;
	BYTE type;
	char len;
	char chat[256];
};
struct SC_PAKET_CHAT_INGAME {
	BYTE size;
	BYTE type;
	char id;
	char len;
	char chat[256];
};
struct SC_PAKET_QUEST_INFO {
	BYTE size;
	BYTE type;
	char len;
	char question[256];
};
struct SC_PAKET_DISCONNECT_RET {
	BYTE size;
	BYTE type;
	char id;
};
struct SC_PAKET_GET_SCORE {
	BYTE size;
	BYTE type;
	char id;
};
//================Client===================//
struct CS_PAKET_CHAT_LOBBY {
	BYTE size;
	BYTE type;
	char len;
	char chat[256];
};
struct CS_PAKET_CHAT_INGAME {
	BYTE size;
	BYTE type;
	char len;
	char chat[256];
};
struct CS_PAKET_LOGIN_INFO {
	BYTE size;
	BYTE type;
	char id[40];
	char pw[40];
};
struct CS_PAKET_NEW_ROOM {
	BYTE size;
	BYTE type;
};
struct CS_PAKET_JOIN_ROOM {
	BYTE size;
	BYTE type;
	char rNum;
};
struct CS_PAKET_DRAW_BOARD {
	BYTE size;
	BYTE type;
	WORD posX;
	WORD posY;
	WORD oldPosX;
	WORD oldPosY;

};
struct CS_PAKET_CHANGE_COLOR {
	BYTE size;
	BYTE type;
	WORD color;
};
struct CS_PAKET_REMOVE_BOARD {
	BYTE size;
	BYTE type;
};
struct CS_PAKET_EXIT_ROOM {
	BYTE size;
	BYTE type;
};
struct CS_PAKET_GIVEUP_TURN {
	BYTE size;
	BYTE type;
};
#pragma pack()