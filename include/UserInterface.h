#pragma once

#include <irrlicht.h>
#include "SharedContext.h"

class UserInterface
{
public:
	UserInterface(SharedContext* p_sharedContext);
	~UserInterface();

	void Draw();

private:
	SharedContext* m_sharedContext;
	irr::video::ITexture* m_crosshair;
};
