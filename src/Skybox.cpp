#include "Skybox.h"
#include "Window.h"
#include "Scene.h"

Skybox::Skybox(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	m_lightRotation = 0.f;
	
	m_lightPivotNode = m_sharedContext->scene->GetSceneManager().addEmptySceneNode(nullptr);
	m_lightPivotNode->setPosition(irr::core::vector3df(0, 1000, 1000));

	m_thunderLight = m_sharedContext->scene->GetSceneManager().addLightSceneNode(m_lightPivotNode);
	m_thunderLight->setPosition(irr::core::vector3df(0, 0, 5000));
	m_thunderLight->setRadius(1000.f);
}

void Skybox::Update()
{
	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() - irr::core::vector3df(0, m_lightRotation, 0));

	m_lightRotation += 75.f * m_sharedContext->deltaTime;

	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() + irr::core::vector3df(0, m_lightRotation, 0));
}
