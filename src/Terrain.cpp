#include "Terrain.h"
#include "Scene.h"
#include "EventManager.h"
#include "Window.h"

Terrain::Terrain(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	irr::scene::ISceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	m_mesh = sceneManager.getMesh("../assets/maps/darkness/map.OBJ");

	// Create node
	m_node = sceneManager.addMeshSceneNode(m_mesh, nullptr, ID_NotActivable);
	m_node->setPosition(irr::core::vector3df(100, -100, -50));
	m_node->setScale(irr::core::vector3df(0.6, 0.6, 0.6));
	m_node->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	for (uint8_t i = 0; i < m_node->getMaterialCount(); ++i)
	{
		// m_node->getMaterial(i).setTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/maps/adrien_first_map/rock.png"));
	}

	// Create collider
	m_collider = sceneManager.createTriangleSelector(m_mesh->getMesh(0), m_node);
	m_node->setTriangleSelector(m_collider);
}