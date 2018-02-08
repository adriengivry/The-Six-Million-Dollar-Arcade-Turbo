#include "Skybox.h"
#include "Window.h"
#include "Scene.h"

Skybox::Skybox(SharedContext* p_sharedContext)
{
	irr::video::ITexture* up = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/up.JPG");
	irr::video::ITexture* dn = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/dn.JPG");
	irr::video::ITexture* lf = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/lf.JPG");
	irr::video::ITexture* rt = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/rt.JPG");
	irr::video::ITexture* ft = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/ft.JPG");
	irr::video::ITexture* bk = p_sharedContext->window->GetDriver()->getTexture("../assets/textures/skybox/bk.JPG");

	m_skyboxNode = p_sharedContext->scene->GetSceneManager().addSkyBoxSceneNode(up, dn, lf, rt, ft, bk, nullptr);

	m_sunNode = p_sharedContext->scene->GetSceneManager().addLightSceneNode(nullptr, irr::core::vector3df(10000, 10000, 0), irr::video::SColorf(1.f, 1.f, 1.f, 1.f), 10000);
	m_sunNode->getLightData().Direction.set(-0.5f, -0.5f, 0);
	m_sunNode->getLightData().AmbientColor.set(1.f, 1.f, 1.f, 0.f);
	m_sunNode->enableCastShadow(true);
	m_sunNode->setLightType(irr::video::E_LIGHT_TYPE::ELT_DIRECTIONAL);
}
