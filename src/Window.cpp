#include "Window.h"

Window::Window()
{
	m_device = irr::createDevice(
		DEVICE_TYPE,
		irr::core::dimension2d<irr::u32>(WINDOW_WIDTH, WINDOW_HEIGHT),
		32,
		WINDOW_FULLSCREEN,
		true,
		WINDOW_VSYNC,
		0);
}

Window::~Window()
{
}
