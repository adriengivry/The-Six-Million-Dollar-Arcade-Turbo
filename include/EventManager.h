#pragma once

#include <irrlicht.h>
#include <map>

class EventManager : public irr::IEventReceiver
{
public:
	EventManager();

	void			InitKeyMaps();
	bool			OnEvent(const irr::SEvent& event) override;
	virtual bool	IsKeyDown(irr::EKEY_CODE keyCode) const;
	irr::SKeyMap*	GetKeyMap(const std::string& keyMap) const;

private:
	bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];
	std::map<std::string, std::pair<irr::SKeyMap*, irr::u16>> m_keyMaps;
};
