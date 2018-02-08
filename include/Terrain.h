#pragma once
#include "SharedContext.h"

class Terrain
{
public:
	explicit Terrain(SharedContext* p_sharedContext);
	~Terrain() = default;

	irr::scene::IAnimatedMesh*			GetMesh()		const { return m_mesh; }
	irr::scene::ITriangleSelector*		GetCollider()	const { return m_collider; }
	irr::scene::IMeshSceneNode*			GetNode()		const { return m_node; }


private:
	SharedContext*						m_sharedContext;
	irr::scene::IAnimatedMesh*			m_mesh;
	irr::scene::IMeshSceneNode*			m_node;
	irr::scene::ITriangleSelector*		m_collider;
};
