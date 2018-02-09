#include "Game.h"
#include "Player.h"

Game::Game()
{
	Setup();
}

Game::~Game()
{
	Close();
}

void Game::Setup()
{
	m_eventManager = new EventManager(&m_sharedContext);
	m_sharedContext.eventManager = m_eventManager;

	m_window = new Window(m_eventManager);
	m_sharedContext.window = m_window;

	m_scene = new Scene(&m_sharedContext);
	m_sharedContext.scene = m_scene;

	m_scene->InitScene();

	m_userInterface = new UserInterface(&m_sharedContext);
}

void Game::Close()
{
	m_sharedContext.Reset();

	delete m_userInterface;
	delete m_scene;
	delete m_eventManager;
	delete m_window;
}

void Game::UpdateDeltaTime()
{
	m_sharedContext.currentTime = m_window->GetDevice()->getTimer()->getTime();
	m_sharedContext.deltaTime = (m_sharedContext.currentTime - m_sharedContext.lastTime) / 1000.f;
	m_sharedContext.lastTime = m_window->GetDevice()->getTimer()->getTime();
}


void Game::Run()
{
	while (m_sharedContext.window->GetDevice()->run())
	{
		Update();
		Draw();
	}
}

void Game::Update()
{
	UpdateDeltaTime();
	irr::core::stringw titre(m_window->GetDriver()->getFPS());
	m_window->GetDevice()->setWindowCaption(titre.c_str());
	m_eventManager->Update();
	m_scene->Update();
	m_userInterface->Update();

	if (m_scene->GetPlayer()->IsPlaying())
	{
		if (m_sharedContext.gameInfo.currentScore > 0.f)
			m_sharedContext.gameInfo.currentScore -= 200.f * m_sharedContext.deltaTime;

		if (m_scene->GetPlayer()->IsShooting())
			m_sharedContext.gameInfo.currentScore -= 500.f * m_sharedContext.deltaTime;

		if (m_scene->GetPlayer()->IsLighting())
			m_sharedContext.gameInfo.currentScore -= 500.f * m_sharedContext.deltaTime;
	}
}

void Game::Draw() const
{
	m_window->GetDriver()->beginScene(true, true, m_window->GetBackgroundColor());

	m_scene->GetSceneManager().drawAll();
	m_userInterface->Draw();

	m_window->GetDriver()->endScene();
}
