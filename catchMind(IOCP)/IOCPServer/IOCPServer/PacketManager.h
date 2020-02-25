#pragma once
#include "Singleton.h"
struct Brush;
class PacketManager : public Singleton<PacketManager>
{
private:

public:
	void	sendPacket(int id, void* packet);
	void	connectPacket(int id);
	void	loginSuccessfulAndNicknamePacket(int id, int sendId, std::string nick);
	void	sendLobbyChatPacket(int id, std::string chat);
	void	sendInGameChatPacket(int id, int sendId, std::string chat);
	void	changeScenePacket(int id, int sNum);
	void	makeNewRoomPacket(int id, int rNum);
	void	informJoinUserPacket(int id, int otherId);
	void	informMatchPacket(int id);
	void	disconnectClientPacket(int id, int sendId);
	void	changeNextTurnPacket(int id, int num);
	void	drawInformInRoomUserPacket(int id, Brush brs);
	void	changeColorPacket(int id, Color color);
	void	exitRoomPacket(int id, int sendId);
	void	removeBoardPacket(int id);
	void	removeRoomPacket(int id, int roomNum);
	void	infromQuestionInfoPacket(int id, std::string question);
	void	infromUsersGetScorePacket(int id, int sendId);
};
