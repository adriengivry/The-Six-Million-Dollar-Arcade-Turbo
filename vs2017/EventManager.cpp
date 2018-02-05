#include "EventManager.h"

EventManager::EventManager()
{
	for (auto& i : KeyIsDown)
		i = false;
}

bool EventManager::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool EventManager::IsKeyDown(const EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}
