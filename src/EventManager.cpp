#include "EventManager.h"

EventManager::EventManager()
{
	for (auto& i : KeyIsDown)
		i = false;
}

bool EventManager::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool EventManager::IsKeyDown(const irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
