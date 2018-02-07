#include "World.h"
#include "Scene.h"
#include "EventManager.h"
#include "Window.h"
#include "Utilities.h"
#include "Player.h"

World::World(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	InitComponents();
}

World::~World()
{
	// TODO: World DESTRUCTOR
}

void World::InitComponents()
{
	irr::scene::ISceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	m_root = sceneManager.addEmptySceneNode();
	m_selector = sceneManager.createMetaTriangleSelector();

	auto cube1 = sceneManager.addCubeSceneNode(300, m_root);
	cube1->setPosition(irr::core::vector3df(0, -400, 0));
	cube1->setScale(irr::core::vector3df(2, 1, 20));
	cube1->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	auto cube2 = sceneManager.addCubeSceneNode(300, m_root);
	cube2->setPosition(irr::core::vector3df(0, 400, 0));
	cube2->setScale(irr::core::vector3df(2, 1, 20));
	cube2->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	auto cube3 = sceneManager.addCubeSceneNode(300, m_root);
	cube3->setPosition(irr::core::vector3df(-400, 0, 0));
	cube3->setRotation(irr::core::vector3df(0, 0, 90));
	cube3->setScale(irr::core::vector3df(2, 1, 20));
	cube3->setMaterialFlag(irr::video::EMF_LIGHTING, true);

	auto cube4 = sceneManager.addCubeSceneNode(300, m_root);
	cube4->setPosition(irr::core::vector3df(400, 0, 0));
	cube4->setRotation(irr::core::vector3df(0, 0, 90));
	cube4->setScale(irr::core::vector3df(2, 1, 20));

	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube1));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube2));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube3));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube4));
}

void World::AddToWorldSelector(irr::scene::ITriangleSelector* p_selector) const
{
	m_selector->addTriangleSelector(p_selector);
}

void World::Update()
{
}
