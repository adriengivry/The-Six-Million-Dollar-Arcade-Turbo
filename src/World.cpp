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

	// Create World root
	m_root = sceneManager.addEmptySceneNode();

	irr::video::ITexture* up = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/up.JPG");
	irr::video::ITexture* dn = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/dn.JPG");
	irr::video::ITexture* lf = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/lf.JPG");
	irr::video::ITexture* rt = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/rt.JPG");
	irr::video::ITexture* ft = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/ft.JPG");
	irr::video::ITexture* bk = m_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/bk.JPG");

	sceneManager.addSkyBoxSceneNode(up, dn, lf, rt, ft, bk, m_root);
	
	// Add Quake map to filesystem
	m_sharedContext->window->GetDevice()->getFileSystem()->addFileArchive("../assets/maps/map-20kdm2.pk3");

	// Load Quake map into an AnimatedMesh
	irr::scene::IAnimatedMesh* q3levelmesh = sceneManager.getMesh("20kdm2.bsp");

	// Create the terrain and his triangleSelector
	m_terrain = sceneManager.addOctreeSceneNode(q3levelmesh->getMesh(0), m_root);
	m_selector = sceneManager.createOctreeTriangleSelector(q3levelmesh->getMesh(0), m_terrain, 128);
	m_terrain->setTriangleSelector(m_selector);
	m_terrain->setPosition(irr::core::vector3df(-1350, -130, -1400));
}