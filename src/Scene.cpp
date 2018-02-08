#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>
#include "Player.h"
#include "World.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->window->GetDevice()->getSceneManager())
{}

void Scene::InitScene()
{
	m_world = new World(m_sharedContext);
	m_player = new Player(m_sharedContext);
}

void Scene::Update()
{
	m_player->Update();
	m_world->Update();
	
}
