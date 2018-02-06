#pragma once
#include "SharedContext.h"

typedef irr::scene::IMetaTriangleSelector Collider;

class World
{
public:
	static const irr::u32 WORLD_ROTATION_ANGLE_PER_SECOND = 360;
	explicit World(SharedContext* p_sharedContext);
	~World();

	void InitComponents();
	void AddToWorldSelector(irr::scene::ITriangleSelector* p_selector) const;

	irr::scene::ISceneNode*	GetRoot()		const { return m_root; }
	Collider*				GetSelector()	const { return m_selector; }

	void Update();

private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneNode*		m_root;
	Collider*					m_selector;
};
