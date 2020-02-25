#pragma once
#include "Singleton.h"
class ProcessManager : public Singleton<ProcessManager>
{
private:

public:
	void	 processPacket(int key, unsigned char* ptr);
	void	 processLogin(int key, unsigned char* ptr);
	void	 processMakeRoom(int key, unsigned char* ptr);
	void	 processJoinRoom(int key, unsigned char* ptr);
	void	 processDrawBoard(int key, unsigned char* ptr);
	void	 processChangeColor(int key, unsigned char* ptr);
	void	 processRemoveBoard(int key, unsigned char* ptr);
	void	 processExitRoom(int key, unsigned char* ptr);
	void	 processChatLoobby(int key, unsigned char* ptr);
	void	 processChatInGame(int key, unsigned char* ptr);
	void	 processGiveupTurn(int key, unsigned char* ptr);
};

