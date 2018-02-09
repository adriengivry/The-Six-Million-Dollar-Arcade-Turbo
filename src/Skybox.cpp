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

	SetSpectateLight();
	
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
}

void Skybox::Update()
{
	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() - irr::core::vector3df(m_lightRotation, m_lightRotation, m_lightRotation));

	m_lightRotation += m_lightRotationSpeed * m_sharedContext->deltaTime;

	m_lightPivotNode->setRotation(m_lightPivotNode->getRotation() + irr::core::vector3df(m_lightRotation, m_lightRotation, m_lightRotation));
}

void Skybox::SetGameLight()
{
	m_lightRotation = 0.f;
	m_thunderLight->setRadius(1000.f);
	m_sharedContext->scene->GetSceneManager().setAmbientLight(irr::video::SColorf(0, 0, 0));
	m_sharedContext->scene->GetTerrain()->GetNode()->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	m_lightRotationSpeed = 50.f;
}

void Skybox::SetSpectateLight()
{
	m_lightRotation = 45.f;
	m_thunderLight->setRadius(5000.f);
	m_sharedContext->scene->GetSceneManager().setAmbientLight(irr::video::SColorf(0.8, 0.8, 0.8));
	m_sharedContext->scene->GetTerrain()->GetNode()->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	m_lightRotationSpeed = 0.f;
}
