#pragma once
#include "stdafx.h"
class Scene
{
public:
	virtual ~Scene() {};
public:
	virtual void initScene() = 0;
	virtual void updateScene() = 0;
	virtual void renderScene(HDC hdc) = 0;
	virtual void releaseScene() = 0;

	virtual void setCheckButton(bool check) = 0;
};