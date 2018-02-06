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
	auto cube = m_sceneManager.addCubeSceneNode(200);
	cube->setPosition(irr::core::vector3df(0, -200, 0));
	irr::scene::ITriangleSelector* selector = nullptr;
	selector = m_sceneManager.createTriangleSelectorFromBoundingBox(cube);
	cube->setTriangleSelector(selector);
	
	m_camera = m_sceneManager.addCameraSceneNodeFPS(
		nullptr, 100.0f, 0.3f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"), true, 3.f);
	irr::scene::ISceneNodeAnimator* anim = m_sceneManager.createCollisionResponseAnimator(
		selector, m_camera, irr::core::vector3df(30, 50, 30),
		irr::core::vector3df(0, -10, 0), irr::core::vector3df(0, 30, 0));
	selector->drop(); // As soon as we're done with the selector, drop it.
	m_camera->addAnimator(anim);
	anim->drop();  // And likewise, drop the animator when we're done referring to it.

	m_fps = m_sceneManager.addAnimatedMeshSceneNode(
			m_sceneManager.getMesh(Utils::LoadAsset("meshes/gun.md2").c_str()),
			m_camera);

	m_fps->setRotation(irr::core::vector3df(0, -90, 0));
	
	m_fps->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/gun.jpg").c_str()));

	m_sceneManager.setAmbientLight(irr::video::SColorf(0.5, 0.5, 0.5, 0.0));

	auto light = m_sceneManager.addLightSceneNode(nullptr, irr::core::vector3df(0, 0, 0), irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f), 100.f);

}

void Scene::Update()
{
}
