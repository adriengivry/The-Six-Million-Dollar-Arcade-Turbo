#pragma once
#include "GameInfo.h"
#include <irrlicht.h>

class Window;
class EventManager;

typedef irr::scene::ISceneManager SceneManager;

struct SharedContext
{
	GameInfo		gameInfo;
	Window*			window;
	SceneManager*	sceneManager;
	EventManager*	eventManager;

	irr::f32 currentTime = 0;
	irr::f32 lastTime = 0;
	irr::f32 deltaTime = 0;

	irr::f32 floorPos = 0;
	bool isJumping = false;
	irr::f32 ySpeed;
	irr::f32 gravityAcc = -50;
};
