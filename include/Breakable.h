#pragma once
#include <irrlicht.h>
#include "SharedContext.h"

class Breakable
{
public:
	Breakable(SharedContext* p_sharedContext, const irr::core::vector3df& p_pos);
	~Breakable() = default;

	irr::scene::IMeshSceneNode*		GetNode()		const { return m_node; }
	irr::scene::ITriangleSelector*	GetCollider()	const { return m_collider; }

	void Destroy();
	void Update();

private:
	SharedContext*					m_sharedContext;
	irr::scene::IMeshSceneNode*		m_node;
	irr::scene::ITriangleSelector*	m_collider;

	irr::f32 m_rotation;
	irr::f32 m_scale;
	bool m_breaking;
	bool m_cleanMePlease;
};
