#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->sceneManager)
{}

void Scene::InitScene()
{
	auto camera = m_sceneManager.addCameraSceneNodeFPS(
		nullptr, 100.0f, 0.05f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"));

	auto sydney = m_sceneManager.addAnimatedMeshSceneNode(
			m_sceneManager.getMesh(Utils::LoadAsset("meshes/sydney.md2").c_str()));

	sydney->setPosition(irr::core::vector3df(0, -20, 40));
	sydney->setRotation(irr::core::vector3df(0, -90, 0));

	sydney->setMD2Animation(irr::scene::EMAT_RUN);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	sydney->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/sydney.bmp").c_str()));

	m_sceneManager.setAmbientLight(irr::video::SColorf(0.0f, 0.0f, 0.0f, 0.f));
	m_sceneManager.addLightSceneNode(nullptr, irr::core::vector3df(0, 0, 50),
		irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f), 100.0f);
}
