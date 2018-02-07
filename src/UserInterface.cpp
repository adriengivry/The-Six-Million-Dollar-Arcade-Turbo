#include "UserInterface.h"
#include "Window.h"
#include "Utilities.h"
#include <iostream>

UserInterface::UserInterface(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;
	m_crosshair = p_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/crosshair.png").c_str());

	m_sharedContext->window->GetDevice()->getCursorControl()->setVisible(false);
}

UserInterface::~UserInterface()
{
}

void UserInterface::Draw()
{
	m_sharedContext->window->GetDriver()->draw2DImage(m_crosshair,
		irr::core::position2d<irr::s32>(Window::WINDOW_WIDTH / 2 - 8, Window::WINDOW_HEIGHT / 2 - 8),
		irr::core::rect<irr::s32>(0, 0, 16, 16),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);
}
