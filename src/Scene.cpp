#include "Scene.h"
#include "EventManager.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>
#include "Player.h"
#include "World.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->window->GetDevice()->getSceneManager())
{}

void Scene::InitScene()
{
	m_world = new World(m_sharedContext);
	m_player = new Player(m_sharedContext);

	auto sun = m_sceneManager.addLightSceneNode(nullptr, irr::core::vector3df(10000, 10000, 0), irr::video::SColorf(1.f, 1.f, 1.f, 1.f), 10000);
	sun->getLightData().Direction.set(-0.5f, -0.5f, 0);
	sun->getLightData().AmbientColor.set(1.f, 1.f, 1.f, 0.f);
	sun->enableCastShadow(true);
	sun->setLightType(irr::video::E_LIGHT_TYPE::ELT_DIRECTIONAL);
}

void Scene::Update()
{
	m_player->Update();
}
