#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InGameScene.h"
#include "LobbyScene.h"
#include "ChatManager.h"
#include "LoginScene.h"
void SceneManager::initScene()
{
	ChatManager::getInstance()->initChat();
	
	sceneNum = SCENE_LOGIN;

	scene.insert(make_pair(SCENE_LOGIN, new LoginScene()));
	scene.insert(make_pair(SCENE_LOBBY, new LobbyScene()));
	scene.insert(make_pair(SCENE_GAME, new InGameScene()));

	for (auto iter = scene.begin(); iter != scene.end(); iter++)
		(*iter).second->initScene();

}
void SceneManager::updateScene()
{
	scene.find(sceneNum)->second->updateScene();
	ChatManager::getInstance()->updateChat();
}
void SceneManager::renderScene(HDC hdc)
{
	scene.find(sceneNum)->second->renderScene(hdc);
	ChatManager::getInstance()->render(hdc);
}
void SceneManager::setCheckButton(bool check) {
	for (auto iter = scene.begin(); iter != scene.end(); iter++)
		(*iter).second->setCheckButton(check);
}
void SceneManager::releaseScene()
{
	for (auto iter = scene.begin(); iter != scene.end(); ++iter) {
		(*iter).second->releaseScene();
		delete (*iter).second;

	}
	scene.clear();
	ChatManager::getInstance()->releaseChat();
	ChatManager::getInstance()->releaseInstance();
}

void SceneManager::changScene(SCENE_NUM scNum)
{
	sceneNum = scNum;
	
	ChatManager::getInstance()->changeSceneNum(scNum);
};


