#pragma once
#include "SharedContext.h"

class World
{
public:
	static const irr::u32 WORLD_ROTATION_ANGLE_PER_SECOND = 360;
	explicit World(SharedContext* p_sharedContext);
	~World();

	void InitComponents();

	irr::scene::ISceneNode*			GetRoot()		const { return m_root; }
	irr::scene::ITriangleSelector*	GetSelector()	const { return m_selector; }

private:
	SharedContext*					m_sharedContext;
	irr::scene::ISceneNode*			m_root;
	irr::scene::IMeshSceneNode*		m_terrain;
	irr::scene::ITriangleSelector*	m_selector;
};
