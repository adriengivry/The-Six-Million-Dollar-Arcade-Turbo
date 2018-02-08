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

	p_sharedContext->scene->GetSceneManager().setAmbientLight(irr::video::SColorf(0.4f, 0.4f, 0.4f, 0.0));

	m_sunNode = p_sharedContext->scene->GetSceneManager().addLightSceneNode(nullptr, irr::core::vector3df(1000, 1000, 1000), irr::video::SColorf(.8f, .8f, .8f, 1.f), 500.f);
}
