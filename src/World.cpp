#include "World.h"
#include "Scene.h"
#include "EventManager.h"

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

	auto cube2 = sceneManager.addCubeSceneNode(100, m_root);
	cube2->setPosition(irr::core::vector3df(0, 500, 0));
	cube2->setScale(irr::core::vector3df(2, 1, 20));

	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube1));
	AddToWorldSelector(sceneManager.createTriangleSelectorFromBoundingBox(cube2));
}

void World::StartRotation()
{
	m_rotating = true;
}

void World::AddToWorldSelector(irr::scene::ITriangleSelector* p_selector) const
{
	m_selector->addTriangleSelector(p_selector);
}

void World::Update()
{
	m_root->setRotation(irr::core::vector3df(0, 0, m_rotation));

	if (m_rotation == 360)
		m_rotation = 0;

	if (m_rotating)
	{
		const auto rotationLimit = IsInverted() ? irr::f32(360.f) : irr::f32(180.f);

		m_rotation += WORLD_ROTATION_ANGLE_PER_SECOND * m_sharedContext->deltaTime;
		if (m_rotation > rotationLimit)
		{
			m_rotation = rotationLimit;
			m_rotating = false;
		}
	}
}
