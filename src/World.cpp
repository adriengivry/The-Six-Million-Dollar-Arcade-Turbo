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

	auto cube1 = sceneManager.addCubeSceneNode(100, m_root);
	cube1->setPosition(irr::core::vector3df(0, -500, 0));
	cube1->setScale(irr::core::vector3df(2, 1, 20));
	cube1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	cube1->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/terrain.jpg").c_str()));

	auto cube2 = sceneManager.addCubeSceneNode(100, m_root);
	cube2->setPosition(irr::core::vector3df(0, 500, 0));
	cube2->setScale(irr::core::vector3df(2, 1, 20));
	cube2->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	cube2->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/terrain.jpg").c_str()));

	auto cube3 = sceneManager.addCubeSceneNode(100, m_root);
	cube3->setPosition(irr::core::vector3df(0, -400, 0));
	cube3->setScale(irr::core::vector3df(2, 1, 1));
	cube3->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	cube3->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/rock.jpg").c_str()));

	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube1));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube2));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube3));
}

void World::AddToWorldSelector(irr::scene::ITriangleSelector* p_selector) const
{
	m_selector->addTriangleSelector(p_selector);
}

void World::Update()
{
}
