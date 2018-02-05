#pragma once
#include "AppInfo.h"
#include "GameInfo.h"

class Window;
class EventManager;

struct SharedContext
{
	GameInfo gameInfo;
	AppInfo appInfo;
	Window* window;
	EventManager* eventManager;
};
