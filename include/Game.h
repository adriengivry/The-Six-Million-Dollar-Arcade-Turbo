#pragma once
#include "Window.h"
#include "SharedContext.h"

class Game
{
public:
	Game();
	~Game();

	void Run()		const;
	void Update()	const;

private:
	SharedContext				m_sharedContext;
	EventManager				m_eventManager;
	Window*						m_window;
	irr::scene::ISceneManager*	m_sceneManager;
};
