#include "Window.h"

Window::Window(EventManager* p_eventManager)
{
	m_device = irr::createDevice(	DEVICE_TYPE,
									WindowSize(WINDOW_WIDTH, WINDOW_HEIGHT),
									irr::u32(32),
									WINDOW_FULLSCREEN,
									WINDOW_STENCILBUFFER,
									WINDOW_VSYNC,
									p_eventManager);

	m_driver = m_device->getVideoDriver();

	m_backgroundColor.set(255,	WINDOW_CLEAR_COLOR_R,
								WINDOW_CLEAR_COLOR_G,
								WINDOW_CLEAR_COLOR_B);
}

Window::~Window()
{
	m_device->drop();
}
