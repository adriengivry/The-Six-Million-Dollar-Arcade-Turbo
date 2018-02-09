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
	ID_Laser = 2 << 0,
};

struct SharedContext
{
	SharedContext() { Reset(); }

	GameInfo		gameInfo;
	Window*			window;
	Scene*			scene;
	EventManager*	eventManager;

	irr::u32 currentTime;
	irr::u32 lastTime;
	irr::f32 deltaTime;
	irr::u32 breakableID;

	void Reset()
	{
		gameInfo.Reset();

		currentTime = 0;
		lastTime = 0;
		deltaTime = 0;
		breakableID = 0;
	}
};
