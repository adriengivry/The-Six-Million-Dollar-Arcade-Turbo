#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

class EventManager : public IEventReceiver
{
public:
	EventManager();
	bool OnEvent(const SEvent& event) override;
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};