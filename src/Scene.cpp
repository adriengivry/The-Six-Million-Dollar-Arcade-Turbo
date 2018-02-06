#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->sceneManager)
{}

void Scene::InitScene()
{
	irr::scene::IMetaTriangleSelector* worldSel = m_sceneManager.createMetaTriangleSelector();

	m_world = m_sceneManager.addEmptySceneNode();

	auto cube = m_sceneManager.addCubeSceneNode(100, m_world);
	cube->setPosition(irr::core::vector3df(0, -500, 0));
	cube->setScale(irr::core::vector3df(2, 1, 20));
	irr::scene::ITriangleSelector* selector = nullptr;
	selector = m_sceneManager.createTriangleSelectorFromBoundingBox(cube);

	auto cube2 = m_sceneManager.addCubeSceneNode(100, m_world);
	cube2->setPosition(irr::core::vector3df(0, 500, 0));
	cube2->setScale(irr::core::vector3df(2, 1, 20));
	irr::scene::ITriangleSelector* selector2 = nullptr;
	selector2 = m_sceneManager.createTriangleSelectorFromBoundingBox(cube2);

	worldSel->addTriangleSelector(selector);
	worldSel->addTriangleSelector(selector2);
	
	m_camera = m_sceneManager.addCameraSceneNodeFPS(
		nullptr, 100.0f, 0.3f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"), true, 1.f);
	irr::scene::ISceneNodeAnimator* anim = m_sceneManager.createCollisionResponseAnimator(
		worldSel, m_camera, irr::core::vector3df(30, 50, 30),
		irr::core::vector3df(0, -1, 0), irr::core::vector3df(0, 30, 0));
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
	if (m_sharedContext->isRotating)
	{
		m_camera->setPosition(irr::core::vector3df(m_camera->getPosition().X, m_sharedContext->playerYbackup, m_camera->getPosition().Z));
	}

	m_world->setRotation(irr::core::vector3df(0, 0, m_sharedContext->worldRotation));

	if (m_sharedContext->eventManager->IsKeyDown(irr::KEY_KEY_X) && !m_sharedContext->isRotating)
	{
		m_sharedContext->isRotating = true;		
		m_sharedContext->playerYbackup = m_camera->getPosition().Y;
	}

	if (m_sharedContext->isRotating)
	{
		if (!m_sharedContext->isInverted)
		{
			m_sharedContext->worldRotation += 600 * m_sharedContext->deltaTime;
			if (m_sharedContext->worldRotation > 180)
			{
				m_sharedContext->worldRotation = 180;
				m_sharedContext->isRotating = false;
				m_sharedContext->isInverted = true;
			}
		}
		else
		{
			m_sharedContext->worldRotation -= 600 * m_sharedContext->deltaTime;
			if (m_sharedContext->worldRotation < 0)
			{
				m_sharedContext->worldRotation = 0;
				m_sharedContext->isRotating = false;
				m_sharedContext->isInverted = false;
			}
		}
	}

	
}
