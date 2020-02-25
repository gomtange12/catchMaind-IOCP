#pragma once

class BitMap;
class Lobby
{
private:
	BitMap*	 back;
	RECT	 makeNewRoomRect;
	bool	 makeNewRoomCheckButton;
	bool	 joinRoomCheckButton;
public:
	void	 initLobby();
	void	 updateLobby();
	void	 renderLobby(HDC hdc);
	void	 makeNewRoomCheck();
	void	 joinRoomCheck();
	void	 release();

	void	 setNewRoomButton(bool check);
};


