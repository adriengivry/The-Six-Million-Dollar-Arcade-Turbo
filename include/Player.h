#pragma once
#include <ICameraSceneNode.h>
#include "SharedContext.h"

typedef irr::scene::ISceneNodeAnimatorCollisionResponse CollisionResponse;

class Player
{
public:
	static const irr::s32 PLAYER_GRAVITY = -2;

	explicit Player(SharedContext* p_sharedContext);
	~Player();

	void InitComponents();
	void Update();

	void Reverse();

	irr::scene::ICameraSceneNode*		GetCamera() const { return m_cameraComponent; }
	irr::scene::IAnimatedMeshSceneNode* GetAnimatedMesh() const { return m_animatedMeshComp; }

private:
	SharedContext*								m_sharedContext;
	irr::scene::ISceneNode*						m_root;
	irr::scene::ICameraSceneNode*				m_cameraComponent;
	irr::scene::ISceneNodeAnimatorCameraFPS*	m_cameraAnimator;
	irr::scene::IAnimatedMeshSceneNode*			m_animatedMeshComp;
	CollisionResponse*							m_collisionResponse;
	irr::f32 m_gravity;
	irr::f32 m_gravityTimer;
	irr::f32 m_gunRotation;
	irr::core::vector3df m_newGunRotation;
};