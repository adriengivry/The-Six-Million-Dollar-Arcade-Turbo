#pragma once

#include <irrlicht.h>
#include "SharedContext.h"

class UserInterface
{
public:
	explicit UserInterface(SharedContext* p_sharedContext);
	~UserInterface() = default;

	void Draw() const;

	void Update();

private:
	SharedContext*					m_sharedContext;
	irr::video::ITexture*			m_crosshair;

	irr::gui::IGUIEnvironment*		m_gui;
	irr::gui::IGUIFont*				m_font;
	irr::gui::IGUISkin*				m_skin;

	irr::gui::IGUIStaticText*		m_scoreText;
	irr::gui::IGUIStaticText*		m_scoreValue;
	irr::gui::IGUIStaticText*		m_titleText;
};
