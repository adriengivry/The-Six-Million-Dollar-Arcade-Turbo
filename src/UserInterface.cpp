#include "UserInterface.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Utilities.h"
#include <iostream>

UserInterface::UserInterface(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;
	m_crosshair = p_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/crosshair.png").c_str());

	m_sharedContext->window->GetDevice()->getCursorControl()->setVisible(false);

	m_gui = p_sharedContext->window->GetDevice()->getGUIEnvironment();

	m_skin = m_gui->getSkin();

	m_font = m_gui->getFont("../assets/fonts/fontcourier.bmp");

	m_skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255));
	
	m_skin->setFont(m_font);

	m_gui->addStaticText(L"SCORE:", irr::core::rect<irr::s32>(30, 30, 200, 50));

	m_gui->addStaticText(irr::core::stringw(m_sharedContext->gameInfo.defaultScore).c_str(), irr::core::rect<irr::s32>(100, 30, 200, 50));
}

UserInterface::~UserInterface()
{

}

void UserInterface::Draw()
{
	m_gui->drawAll();

	m_sharedContext->window->GetDriver()->draw2DImage(m_crosshair,
		irr::core::position2d<irr::s32>(Window::WINDOW_WIDTH / 2 - 8, Window::WINDOW_HEIGHT / 2 - 8),
		irr::core::rect<irr::s32>(0, 0, 16, 16),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);
}

void UserInterface::Update()
{
	/*while (m_sharedContext->gameInfo.defaultScore > 0.0f)
	{
		m_sharedContext->gameInfo.defaultScore -= 1 * m_sharedContext->deltaTime;
	}*/
}