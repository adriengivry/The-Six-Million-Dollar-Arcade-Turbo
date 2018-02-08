#pragma once

#include <irrlicht.h>

#include "SharedContext.h"

class Skybox
{
public:
	explicit Skybox(SharedContext* p_sharedContext);
	~Skybox() = default;

	irr::scene::ISceneNode* GetNode() const { return m_skyboxNode; }
	irr::scene::ILightSceneNode* GetSunNode() const { return m_sunNode; }

private:
	irr::scene::ISceneNode* m_skyboxNode;
	irr::scene::ILightSceneNode* m_sunNode;
};