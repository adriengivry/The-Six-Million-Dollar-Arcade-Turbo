#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>
#include "Player.h"
#include "Breakable.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->window->GetDevice()->getSceneManager())
{}

void Scene::InitScene()
{
	m_skybox = new Skybox(m_sharedContext);
	m_terrain = new Terrain(m_sharedContext);

	m_breakables.push_back(new Breakable(m_sharedContext, irr::core::vector3df(-20, -10, 430)));
	m_breakables.push_back(new Breakable(m_sharedContext, irr::core::vector3df(-20, -70, 430)));
	
	m_worldCollider = m_sceneManager.createMetaTriangleSelector();
	m_worldCollider->addTriangleSelector(m_terrain->GetCollider());
	
	for (auto breakable : m_breakables)
		m_worldCollider->addTriangleSelector(breakable->GetCollider());

	m_player = new Player(m_sharedContext);
}

void Scene::Update()
{
	m_player->Update();
	m_skybox->Update();

	for (auto breakable : m_breakables)
		breakable->Update();
}
