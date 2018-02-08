#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>
#include "Player.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->window->GetDevice()->getSceneManager())
{}

void Scene::InitScene()
{
	m_skybox = new Skybox(m_sharedContext);
	m_terrain = new Terrain(m_sharedContext);
	m_player = new Player(m_sharedContext);
}

void Scene::Update() const
{
	m_player->Update();
}
