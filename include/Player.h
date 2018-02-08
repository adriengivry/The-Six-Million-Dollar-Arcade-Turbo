#pragma once
#include <ICameraSceneNode.h>
#include "SharedContext.h"

typedef irr::scene::ISceneNodeAnimatorCollisionResponse CollisionResponse;

class Player
{
public:
	static const irr::s32 PLAYER_GRAVITY = -10;

	explicit Player(SharedContext* p_sharedContext);
	~Player();

	void InitComponents();
	void Update();

	void Reverse();
	void RotateGun();
	void TranslateGun();
	void UpdateRayLength();

	irr::scene::ICameraSceneNode*		GetCamera() const { return m_cameraComponent; }
	irr::scene::IAnimatedMeshSceneNode* GetArmsAndGun() const { return m_armsAndGun; }
	CollisionResponse*					GetCollider() const { return m_collisionResponse; }

private:
	SharedContext*								m_sharedContext;
	irr::scene::ISceneNode*						m_root;
	irr::scene::ICameraSceneNode*				m_cameraComponent;
	irr::scene::ISceneNodeAnimatorCameraFPS*	m_cameraAnimator;
	irr::scene::IAnimatedMeshSceneNode*			m_armsAndGun;
	irr::scene::IMeshSceneNode*					m_gunRay;
	CollisionResponse*							m_collisionResponse;
	irr::scene::IParticleSystemSceneNode*		m_particleSystem;

	irr::scene::ILightSceneNode* m_gunLight;

	irr::f32 m_gravity;
	irr::f32 m_gravityTimer;
	irr::f32 m_gunRotation;
	irr::f32 m_gunTranslation;

	bool m_mouseInverted;
	bool m_invertEnd;
	bool m_reversing;

	bool m_shooting;

	irr::f32 m_rayLength;
};
