#include "Game.h"

Game::Game()
{
	m_window	= new Window(&m_eventManager);

	// Update SharedContext pointers
	m_sharedContext.window			= m_window;
	m_sharedContext.sceneManager	= m_window->GetDevice()->getSceneManager();
	m_sharedContext.eventManager	= &m_eventManager;

	m_scene = new Scene(&m_sharedContext);
}

Game::~Game()
{
	delete m_scene;
	delete m_window;
}


void Game::Run() const
{
	while (m_sharedContext.window->GetDevice()->run())
		Update();
}

void Game::Update() const
{
	m_window->GetDriver()->beginScene(true, true, m_window->GetBackgroundColor());

	m_scene->GetSceneManager().drawAll();

	m_window->GetDriver()->endScene();
}
