#include "stdafx.h"
#include "LobbyScene.h"
#include "Lobby.h"
void LobbyScene::initScene()
{
	lobby = new Lobby();
	lobby->initLobby();
}
void LobbyScene::updateScene()
{
	lobby->updateLobby();
}

void LobbyScene::renderScene(HDC hdc)
{
	lobby->renderLobby(hdc);
}

void LobbyScene::releaseScene()
{
	lobby->release();
	delete lobby;
}

void LobbyScene::setCheckButton(bool check) {
	lobby->setNewRoomButton(check);
}