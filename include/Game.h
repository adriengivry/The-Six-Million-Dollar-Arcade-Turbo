#pragma once
#include "Window.h"
#include "SharedContext.h"

class Game
{
public:
	Game();
	~Game();

	void Setup();
	void Close();
	void Run();
	void Update();

private:
	SharedContext m_sharedContext;
	Window m_window;
};
