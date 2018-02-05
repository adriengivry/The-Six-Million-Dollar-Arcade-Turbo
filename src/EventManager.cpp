#include "EventManager.h"

EventManager::EventManager()
{
	for (auto& i : m_keyIsDown)
		i = false;
}

void EventManager::InitKeyMaps()
{
	// Set FPS_CAMERA KeyMap size
	m_keyMaps["FPS_CAMERA"].second = 5;

	const auto fpsKeyMap = new irr::SKeyMap[sizeof(irr::SKeyMap) * m_keyMaps["FPS_CAMERA"].second];
	fpsKeyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
	fpsKeyMap[0].KeyCode = irr::KEY_KEY_W;        // w
	fpsKeyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
	fpsKeyMap[1].KeyCode = irr::KEY_KEY_S;        // s
	fpsKeyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
	fpsKeyMap[2].KeyCode = irr::KEY_KEY_A;        // a
	fpsKeyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
	fpsKeyMap[3].KeyCode = irr::KEY_KEY_D;        // d
	fpsKeyMap[4].Action = irr::EKA_JUMP_UP;       // saut
	fpsKeyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace

	m_keyMaps["FPS_CAMERA"].first = fpsKeyMap;
}

bool EventManager::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		m_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool EventManager::IsKeyDown(const irr::EKEY_CODE keyCode) const
{
	return m_keyIsDown[keyCode];
}

irr::SKeyMap* EventManager::GetKeyMap(const std::string& keyMap) const
{
	return nullptr;
}
