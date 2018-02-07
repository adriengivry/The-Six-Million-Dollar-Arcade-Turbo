#pragma once

#include "SharedContext.h"
#include <irrlicht.h>
#include <map>

class EventManager : public irr::IEventReceiver
{
public:
	EventManager(SharedContext* p_sharedContext);
	~EventManager();

	void			InitKeyMaps();
	void			Update() const;
	bool			OnEvent(const irr::SEvent& event) override;
	virtual bool	IsKeyDown(irr::EKEY_CODE keyCode) const;
	irr::SKeyMap*	GetKeyMap(const std::string& keyMap)		{ return m_keyMaps["FPS_CAMERA"].first; }
	irr::s32		GetKeyMapSize(const std::string& keyMap)	{ return m_keyMaps["FPS_CAMERA"].second; }
	bool			MouseLeftPressed() const { return m_mouseLeft; }
	void			Activate();

private:
	SharedContext* m_sharedContext;
	bool m_keyIsDown[irr::KEY_KEY_CODES_COUNT];
	std::map<std::string, std::pair<irr::SKeyMap*, irr::u16>> m_keyMaps;
	bool m_mouseLeft;
	bool m_activate;
};
