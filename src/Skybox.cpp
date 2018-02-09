#include "Skybox.h"
#include "Window.h"
#include "Scene.h"

Skybox::Skybox(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	m_lightRotation = 0.f;
	
	m_lightPivotNode = m_sharedContext->scene->GetSceneManager().addEmptySceneNode(nullptr);
	m_lightPivotNode->setPosition(irr::core::vector3df(1000, 0, 1000));

	m_thunderLight = m_sharedContext->scene->GetSceneManager().addLightSceneNode(m_lightPivotNode);
	m_thunderLight->setPosition(irr::core::vector3df(0, 0, 3000));
	m_thunderLight->setRadius(1000.f);

	m_sharedContext->scene->GetSceneManager().setAmbientLight(irr::video::SColorf(0, 0, 0));
	

	m_sharedContext->window->GetDriver()->setFog(
		irr::video::SColor(0, 0, 0, 0),
		irr::video::EFT_FOG_LINEAR,
		1000.f,
		5000.0f,
		0.01f,
		true,
		true);

}

Skybox::~Skybox()
{
	m_thunderLight->drop();
	m_lightPivotNode->drop();
}

void Skybox::Update()
{
	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() - irr::core::vector3df(m_lightRotation, m_lightRotation, m_lightRotation));

	m_lightRotation += 50.f * m_sharedContext->deltaTime;

	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() + irr::core::vector3df(m_lightRotation, m_lightRotation, m_lightRotation));
}
