#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

class EventManager : public irr::IEventReceiver
{
public:
	EventManager();

	bool			OnEvent(const irr::SEvent& event) override;
	virtual bool	IsKeyDown(irr::EKEY_CODE keyCode) const;

private:
	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};