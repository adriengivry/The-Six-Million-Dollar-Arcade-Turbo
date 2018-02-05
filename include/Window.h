#pragma once
#include <irrlicht.h>

typedef irr::video::E_DRIVER_TYPE DriverType;

class Window
{
public:
	const irr::u32		WINDOW_WIDTH		= 800;
	const irr::u32		WINDOW_HEIGHT		= 600;
	const bool			WINDOW_FULLSCREEN	= false;
	const bool			WINDOW_VSYNC		= false;
	const DriverType	DEVICE_TYPE			= irr::video::EDT_OPENGL;
	
	Window();
	~Window();

	irr::IrrlichtDevice* GetDevice() const { return m_device; }

private:
	irr::IrrlichtDevice* m_device;
};
