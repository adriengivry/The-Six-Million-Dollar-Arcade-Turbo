#include "Game.h"

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
	// TODO: Game setup
}

void Game::Close()
{
	// TODO: Game close
}

void Game::Run()
{
	while (m_sharedContext.appInfo.isRunning)
		Update();
}

void Game::Update()
{
	// TODO: Game update
}
