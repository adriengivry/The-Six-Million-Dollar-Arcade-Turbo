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

	auto light = m_sceneManager.addLightSceneNode(m_player->GetCamera(), irr::core::vector3df(0, 10, 0),
		irr::video::SColorf(0.4f, 0.4f, 0.4f, 0.0f), 100.f);

	light->getLightData().DiffuseColor = irr::video::SColorf(0.6, 1.0, 1.0, 1);
	light->getLightData().SpecularColor = irr::video::SColorf(0.6, 0.0, 0.0, 1);
}

void Scene::Update()
{
	m_player->Update();
	m_world->Update();
	
}
