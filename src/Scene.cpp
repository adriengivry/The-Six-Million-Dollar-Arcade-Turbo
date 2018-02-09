#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>
#include "Player.h"
#include "Breakable.h"

Scene::Scene(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;
	m_sceneManager = m_sharedContext->window->GetDevice()->getSceneManager();
}

Scene::~Scene()
{
	Close();

}

void Scene::Setup()
{
	m_terrain = new Terrain(m_sharedContext);
	m_skybox = new Skybox(m_sharedContext);

	// Static Blocks
	AddBlock(-20, -10, 430);
	AddBlock(-20, -70, 430);
	AddBlock(20, 75, 2480);
	AddBlock(-50, 75, 2480);
	AddBlock(-22, 430, 3180);
	AddBlock(70, 830, 3420);
	AddBlock(-10, 830, 3420);
	AddBlock(-105, 830, 3420);
	AddBlock(610, 400, 3260);

	// Rotating Blocks


	// Floating Blocks


	m_worldCollider = m_sceneManager->createMetaTriangleSelector();
	m_worldCollider->addTriangleSelector(m_terrain->GetCollider());

	for (auto breakable : m_breakables)
		m_worldCollider->addTriangleSelector(breakable->GetCollider());

	m_player = new Player(m_sharedContext);
}

void Scene::Close()
{
	delete m_player;

	m_breakables.empty();

	delete m_terrain;
	delete m_skybox;

	m_worldCollider->removeAllTriangleSelectors();
}

void Scene::Update()
{
	m_player->Update();
	m_skybox->Update();

	for (auto breakable : m_breakables)
		breakable->Update();
}

void Scene::AddBlock(const irr::f32 p_x, const irr::f32 p_y, const irr::f32 p_z, const irr::u16 p_blockSize)
{
	m_breakables.push_back(new Breakable(m_sharedContext, irr::core::vector3df(p_x, p_y, p_z), p_blockSize));
}
