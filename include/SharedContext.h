#pragma once
#include "GameInfo.h"
#include <irrlicht.h>

class Window;
class EventManager;
class Scene;

typedef irr::scene::ISceneManager SceneManager;

enum
{
	ID_NotActivable = 0,
	ID_Activable = 1 << 0,
};

struct SharedContext
{
	GameInfo		gameInfo;
	Window*			window;
	Scene*			scene;
	EventManager*	eventManager;

	irr::u32 currentTime = 0;
	irr::u32 lastTime = 0;
	irr::f32 deltaTime = 0;
};
