#pragma once
#include <ICameraSceneNode.h>
#include <IAnimatedMesh.h>
#include "SharedContext.h"

class Player
{
public:
	explicit Player(SharedContext* p_sharedContext);
	~Player();

	void InitComponents();
	void Update();

	irr::scene::ICameraSceneNode* GetCamera() const { return m_cameraComponent; }
	irr::scene::IAnimatedMeshSceneNode* GetAnimatedMesh() const { return m_animatedMeshComp; }

private:
	SharedContext*							m_sharedContext;
	irr::scene::ICameraSceneNode*			m_cameraComponent;
	irr::scene::IAnimatedMeshSceneNode*		m_animatedMeshComp;
	irr::f32 m_yPositionMemory;
};
