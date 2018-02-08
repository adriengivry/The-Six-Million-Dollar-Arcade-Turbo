#include "Terrain.h"
#include "Scene.h"
#include "EventManager.h"
#include "Window.h"

Terrain::Terrain(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	irr::scene::ISceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	m_sharedContext->window->GetDevice()->getFileSystem()->addFileArchive("../assets/maps/map-20kdm2.pk3");
	m_mesh = sceneManager.getMesh("20kdm2.bsp");

	// Create node
	m_node = sceneManager.addOctreeSceneNode(m_mesh, nullptr, ID_NotActivable);
	m_node->setPosition(irr::core::vector3df(-1300, -144, -1249));

	// Create collider
	m_collider = sceneManager.createTriangleSelector(m_mesh->getMesh(0), m_node);
	m_node->setTriangleSelector(m_collider);
}