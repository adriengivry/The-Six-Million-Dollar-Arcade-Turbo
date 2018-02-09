#pragma once

#include <irrlicht.h>

#include "SharedContext.h"

class Skybox
{
public:
	explicit Skybox(SharedContext* p_sharedContext);
	~Skybox();

	void Update();

private:
	SharedContext* m_sharedContext;

	irr::scene::ISceneNode*					m_lightPivotNode;
	irr::scene::ILightSceneNode*			m_thunderLight;

	irr::f32 m_lightRotation;
};