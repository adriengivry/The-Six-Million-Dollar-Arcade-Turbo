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

	m_sceneManager.setAmbientLight(irr::video::SColorf(.7f, .7f, .7f, 0.0));
	m_sceneManager.addLightSceneNode(nullptr, irr::core::vector3df(0, 0, 0),
		irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f), 100.0f);
}

void Scene::Update()
{
	m_player->Update();
	m_world->Update();
	
}
