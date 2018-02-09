#include "UserInterface.h"
#include "Window.h"
#include "Scene.h"
#include "Player.h"
#include "Utilities.h"
#include <iostream>

UserInterface::UserInterface(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	// Create crosshait
	m_crosshair = p_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/crosshair.png").c_str());
	m_sharedContext->window->GetDevice()->getCursorControl()->setVisible(false);

	// Create GUI and font
	m_gui = p_sharedContext->window->GetDevice()->getGUIEnvironment();
	m_skin = m_gui->getSkin();
	m_font = m_gui->getFont("../assets/fonts/fontcourier.bmp");
	m_skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255));
	m_skin->setFont(m_font);

	// Create StaticTexts
	m_scoreText = m_gui->addStaticText(L"SCORE:", irr::core::rect<irr::s32>(30, 30, 200, 50));
	m_titleText = m_gui->addStaticText(L"PRESS [ENTER] TO GO TO HELL", irr::core::rect<irr::s32>(Window::WINDOW_WIDTH / 2 - 50, Window::WINDOW_HEIGHT / 2, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT));
	m_howToPlayText = m_gui->addStaticText(L"GOAL: Reach the end\n\nCOMMANDS: [X] to reverse gravity\n[Mouse Left] to shoot cubes\n[Mouse Right] to use your light\n\nTIPS: The less you use your light and gun,\nthe higher your score will be", irr::core::rect<irr::s32>(Window::WINDOW_WIDTH / 2 - 50, Window::WINDOW_HEIGHT / 2 + 50, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT));
	m_lastScoreText = m_gui->addStaticText(L"", irr::core::rect<irr::s32>(Window::WINDOW_WIDTH / 2 - 50, Window::WINDOW_HEIGHT / 2 + 350, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT));
	m_highscoreText = m_gui->addStaticText(L"", irr::core::rect<irr::s32>(Window::WINDOW_WIDTH / 2 - 50, Window::WINDOW_HEIGHT / 2 + 375, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT));

}

UserInterface::~UserInterface()
{
}

void UserInterface::Draw() const
{
	if (m_sharedContext->scene->GetPlayer()->IsPlaying())
	{
		m_scoreText->draw();

		m_sharedContext->window->GetDriver()->draw2DImage(m_crosshair,
			irr::core::position2d<irr::s32>(Window::WINDOW_WIDTH / 2 - 8, Window::WINDOW_HEIGHT / 2 - 8),
			irr::core::rect<irr::s32>(0, 0, 16, 16),
			0,
			irr::video::SColor(255, 255, 255, 255),
			true);
	}
	else
	{
		m_titleText->draw();
		m_howToPlayText->draw();
		m_lastScoreText->draw();
		m_highscoreText->draw();
	}
}

void UserInterface::Update() const
{
	if (m_sharedContext->scene->GetPlayer()->IsPlaying())
	{
		std::string score = "SCORE:" + std::to_string(static_cast<irr::u32>(m_sharedContext->gameInfo.currentScore));
		m_scoreText->setText(irr::core::stringw(score.c_str()).c_str());
	}

	std::string lastScore = "LAST SCORE:" + std::to_string(static_cast<irr::u32>(m_sharedContext->lastScore));
	m_lastScoreText->setText(irr::core::stringw(lastScore.c_str()).c_str());

	std::string highestScore = "HIGHEST SCORE:" + std::to_string(static_cast<irr::u32>(m_sharedContext->highestScore));
	m_highscoreText->setText(irr::core::stringw(highestScore.c_str()).c_str());
}
