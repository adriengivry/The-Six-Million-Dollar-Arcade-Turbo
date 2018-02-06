#include "EventManager.h"
#include "Scene.h"
#include "World.h"

EventManager::EventManager(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	for (auto& i : m_keyIsDown)
		i = false;

	InitKeyMaps();
}

EventManager::~EventManager()
{
	for (auto keyMap : m_keyMaps)
		delete keyMap.second.first;
}

void EventManager::InitKeyMaps()
{
	// Set FPS_CAMERA KeyMap size
	m_keyMaps["FPS_CAMERA"].second = 5;

	const auto fpsKeyMap = new irr::SKeyMap[sizeof(irr::SKeyMap) * m_keyMaps["FPS_CAMERA"].second];

	fpsKeyMap[0].Action		= irr::EKA_MOVE_FORWARD;
	fpsKeyMap[0].KeyCode	= irr::KEY_KEY_W;
	fpsKeyMap[1].Action		= irr::EKA_MOVE_BACKWARD;
	fpsKeyMap[1].KeyCode	= irr::KEY_KEY_S;
	fpsKeyMap[2].Action		= irr::EKA_STRAFE_LEFT;
	fpsKeyMap[2].KeyCode	= irr::KEY_KEY_A;
	fpsKeyMap[3].Action		= irr::EKA_STRAFE_RIGHT;
	fpsKeyMap[3].KeyCode	= irr::KEY_KEY_D;
	fpsKeyMap[4].Action		= irr::EKA_JUMP_UP;
	fpsKeyMap[4].KeyCode	= irr::KEY_SPACE;

	m_keyMaps["FPS_CAMERA"].first = fpsKeyMap;
}

void EventManager::Update() const
{
	if (IsKeyDown(irr::KEY_KEY_X))
	{
		m_sharedContext->scene->GetWorld()->StartRotation();
	}
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
