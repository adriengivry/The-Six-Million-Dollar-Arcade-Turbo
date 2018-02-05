#include "Game.h"

Game::Game()
{
	m_window		= new Window(&m_eventManager);
	m_sceneManager	= m_window->GetDevice()->getSceneManager();

	// Update the sharedContext pointers
	m_sharedContext.window			= m_window;
	m_sharedContext.sceneManager	= m_sceneManager;
	m_sharedContext.eventManager	= &m_eventManager;
}

Game::~Game()
{
	// Deleting window will drop the device too
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

	m_sceneManager->drawAll();

	m_window->GetDriver()->endScene();
}
