#pragma once
#include "Singleton.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	SCENE_NUM			sceneNum;
	map<int, Scene*>	scene;
public:
	void		initScene();
	void		updateScene();
	void		renderScene(HDC hdc);
	void		setCheckButton(bool check);
	void		releaseScene();
	void		changScene(SCENE_NUM scNum);

public:
	inline SCENE_NUM	getSceneNum() { return sceneNum; }
};

