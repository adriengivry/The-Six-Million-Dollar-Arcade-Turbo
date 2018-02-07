#include "Player.h"
#include "EventManager.h"
#include "Scene.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>

Player::Player(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;
	m_gravity = PLAYER_GRAVITY;
	m_gunRotation = 0.f;
	m_mouseInverted = false;
	m_invertEnd = true;
	m_reversing = false;
	m_shooting = false;

	InitComponents();
}

Player::~Player()
{
	m_collisionResponse->drop();
}

void Player::InitComponents()
{
	SceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	m_root = sceneManager.addEmptySceneNode();
	
	irr::SKeyMap*	fpsKeyMap		= m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA");
	const irr::s32	fpsKeyMapSize	= m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA");

	// Camera Component
	m_cameraComponent = sceneManager.addCameraSceneNodeFPS(m_root, 100.0f, 0.3f, -1, fpsKeyMap, fpsKeyMapSize, true, 1.f);

	// Camera Animator
	m_cameraAnimator = static_cast<irr::scene::ISceneNodeAnimatorCameraFPS*>(*m_cameraComponent->getAnimators().begin());

	// Camera Collider
	m_collisionResponse = sceneManager.createCollisionResponseAnimator(m_sharedContext->scene->GetWorld()->GetSelector(), m_cameraComponent);
	m_collisionResponse->setGravity(irr::core::vector3df(0, m_gravity, 0));
	m_cameraComponent->addAnimator(m_collisionResponse);

	// Animated FPS arms
	m_animatedMeshComp = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/gun.md2").c_str()), m_cameraComponent);
	m_animatedMeshComp->setRotation(irr::core::vector3df(0, -90, 0));
	m_animatedMeshComp->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/gun.jpg").c_str()));

	const irr::core::vector3df gunExitPoint(9, -8, 30);

	// gun ray
	m_gunRay = sceneManager.addMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/ray.obj").c_str()), m_cameraComponent);
	m_gunRay->setPosition(gunExitPoint);

	// Gun ray particules
	m_particleSystem = sceneManager.addParticleSystemSceneNode(true, m_cameraComponent);
	m_particleSystem->setPosition(gunExitPoint + irr::core::vector3df(0, 0, 10));
	irr::scene::IParticleAffector* affector = m_particleSystem->createGravityAffector();
	m_particleSystem->addAffector(affector);

}

void Player::Update()
{
	m_gravityTimer += m_sharedContext->deltaTime;

	RotateGun();
	HandleEvents();
}

void Player::Reverse()
{
	if (m_gravityTimer >= 1.f)
	{
		m_reversing = true;
		m_invertEnd = false;
		m_gravityTimer = 0.f;
		m_gravity *= -1;
		m_collisionResponse->setGravity(irr::core::vector3df(0, m_gravity, 0));
	}
}

void Player::RotateGun()
{
	m_animatedMeshComp->setRotation(m_animatedMeshComp->getRotation() - irr::core::vector3df(0, 0, m_gunRotation));

	if (m_gravity > 0)
	{
		m_gunRotation += 600 * m_sharedContext->deltaTime;

		if (m_gunRotation > 180.f)
		{
			m_gunRotation = 180.f;
			m_reversing = false;
		}
	}
	else
	{
		m_gunRotation -= 600 * m_sharedContext->deltaTime;

		if (m_gunRotation < 0.f)
		{
			m_gunRotation = 0.f;
			m_reversing = false;
		}
	}

	m_animatedMeshComp->setRotation(m_animatedMeshComp->getRotation() + irr::core::vector3df(0, 0, m_gunRotation));
}

void Player::HandleEvents()
{
	m_shooting = m_sharedContext->eventManager->MouseLeftPressed();

	m_gunRay->setVisible(m_shooting);
	m_particleSystem->setVisible(m_shooting);
}
