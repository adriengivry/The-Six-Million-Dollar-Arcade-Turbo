#include "Game.h"

Game::Game()
{
	m_window	= new Window(&m_eventManager);

	// Update SharedContext pointers
	m_sharedContext.window			= m_window;
	m_sharedContext.sceneManager	= m_window->GetDevice()->getSceneManager();
	m_sharedContext.eventManager	= &m_eventManager;

	m_scene = new Scene(&m_sharedContext);

	m_scene->InitScene();
}

Game::~Game()
{
	delete m_scene;
	delete m_window;
}


void Game::Run()
{
	while (m_sharedContext.window->GetDevice()->run())
		Update();
}

void Game::Update()
{
	m_sharedContext.currentTime = m_window->GetDevice()->getTimer()->getTime();
	m_sharedContext.deltaTime = (m_sharedContext.currentTime - m_sharedContext.lastTime) / 1000.f;
	m_sharedContext.lastTime = m_window->GetDevice()->getTimer()->getTime();

	m_window->GetDriver()->beginScene(true, true, m_window->GetBackgroundColor());

	irr::core::stringw titre(m_window->GetDriver()->getFPS());
	m_window->GetDevice()->setWindowCaption(titre.c_str());
	m_scene->Update();
	m_scene->GetSceneManager().drawAll();

	m_window->GetDriver()->endScene();

	
}
