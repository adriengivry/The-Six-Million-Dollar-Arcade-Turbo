#include "Scene.h"
#include "EventManager.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->sceneManager)
{}

void Scene::InitScene()
{
	irr::scene::IMeshSceneNode* cube = m_sceneManager.addCubeSceneNode(10.0f);
	cube->setPosition(irr::core::vector3df(0.0f, 0.0f, 20.0f));
	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


	m_sceneManager.addCameraSceneNodeFPS(
		nullptr, 100.0f, 0.1f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"));
}
