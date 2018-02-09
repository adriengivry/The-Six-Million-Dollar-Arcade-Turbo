#pragma once
#include <irrlicht.h>
#include "EventManager.h"

typedef irr::video::E_DRIVER_TYPE DriverType;
typedef irr::core::dimension2d<irr::u32> WindowSize;

class Window
{
public:
	static const irr::u32		WINDOW_WIDTH			= 1920;
	static const irr::u32		WINDOW_HEIGHT			= 1080;
	static const bool			WINDOW_FULLSCREEN		= true;
	static const bool			WINDOW_VSYNC			= true;
	static const bool			WINDOW_STENCILBUFFER	= false;
	static const irr::u32		WINDOW_CLEAR_COLOR_R	= 0;
	static const irr::u32		WINDOW_CLEAR_COLOR_G	= 0;
	static const irr::u32		WINDOW_CLEAR_COLOR_B	= 0;
	static const DriverType		DEVICE_TYPE				= irr::video::EDT_OPENGL;

	explicit Window(EventManager* p_eventManager = nullptr);
	~Window();

	irr::IrrlichtDevice*		GetDevice() const		{ return m_device; }
	irr::video::IVideoDriver*	GetDriver() const		{ return m_driver; }
	irr::video::SColor&			GetBackgroundColor()	{ return m_backgroundColor; }
private:
	irr::IrrlichtDevice*		m_device;
	irr::video::IVideoDriver*	m_driver;
	irr::video::SColor			m_backgroundColor;
};
