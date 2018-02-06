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
	void StartRotation();
	void AddToWorldSelector(irr::scene::ITriangleSelector* p_selector) const;

	irr::scene::ISceneNode*	GetRoot()		const { return m_root; }
	Collider*				GetSelector()	const { return m_selector; }

	void Update();

	bool IsRotating() const { return m_rotating; }
	bool IsInverted() const { return m_rotation >= 180; }

private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneNode*		m_root;
	Collider*					m_selector;
	irr::f32					m_rotation;
	bool						m_rotating;
};
