#pragma once
#include <ICameraSceneNode.h>
#include "SharedContext.h"

class Player
{
public:
	static const irr::s32 PLAYER_MIN_Y_KILL = -2000.f;
	static const irr::s32 PLAYER_MAX_Y_KILL	= 2000.f;

	explicit Player(SharedContext* p_sharedContext);
	~Player() = default;

	void CreateCamera();
	void CreateGun();

	void Update();
	void UpdateGun();
	void UpdateRay();

	void RotateGun();
	void TranslateGun();
	void UpdateRayLength();
	void UpdateRayCollider();

	void Reverse();
	void CheckDeath() const;

	bool IsShooting() const;
	bool CanReverse() const;

	irr::scene::ICameraSceneNode*						GetCameraNode()		const { return m_cameraNode; }
	irr::scene::IAnimatedMeshSceneNode*					GetGunNode()		const { return m_gunNode; }
	irr::scene::ISceneNodeAnimatorCollisionResponse*	GetCollider()		const { return m_cameraCollider; }

private:
	SharedContext* m_sharedContext;

	irr::scene::ICameraSceneNode*			m_cameraNode;
	irr::scene::IAnimatedMeshSceneNode*		m_gunNode;
	irr::scene::IAnimatedMeshSceneNode*		m_rayNode;
	irr::scene::ILightSceneNode*			m_gunLightNode;

	irr::scene::ISceneNodeAnimatorCollisionResponse*	m_cameraCollider;
	irr::scene::ISceneNodeAnimatorCameraFPS*			m_cameraAnimator;

	irr::f32 m_gravity;
	irr::f32 m_gravityTimer;
	irr::f32 m_gunRotation;
	irr::f32 m_gunTranslation;
	irr::f32 m_rayLength;
	irr::f32 m_fallingTimer;

	bool m_mouseInverted;	
};
