#pragma once

#include <irrlicht.h>

#include "SharedContext.h"

class Skybox
{
public:
	explicit Skybox(SharedContext* p_sharedContext);
	~Skybox() = default;

	irr::scene::ISceneNode* GetNode() const { return m_skyboxNode; }

private:
	irr::scene::ISceneNode* m_skyboxNode;
};