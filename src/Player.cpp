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
	
	// Camera Component
	m_cameraComponent = sceneManager.addCameraSceneNodeFPS(
		m_root, 100.0f, 0.3f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"), true, 1.f);

	// Get Camera Animator
	m_cameraAnimator = static_cast<irr::scene::ISceneNodeAnimatorCameraFPS*>(*m_cameraComponent->getAnimators().begin());

	// Camera Collider
	m_collisionResponse = sceneManager.createCollisionResponseAnimator(
		m_sharedContext->scene->GetWorld()->GetSelector(), m_cameraComponent, irr::core::vector3df(30, 50, 30),
		irr::core::vector3df(0, -1, 0), irr::core::vector3df(0, 30, 0));
	m_cameraComponent->addAnimator(m_collisionResponse);

	// Animated FPS arms
	m_animatedMeshComp = sceneManager.addAnimatedMeshSceneNode(
		sceneManager.getMesh(Utils::LoadAsset("meshes/gun.md2").c_str()),
		m_cameraComponent);
	m_animatedMeshComp->setRotation(irr::core::vector3df(0, -90, 0));
	m_animatedMeshComp->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/gun.jpg").c_str()));
}

void Player::Update()
{
	m_gravityTimer += m_sharedContext->deltaTime;

	m_animatedMeshComp->setRotation(m_animatedMeshComp->getRotation() - irr::core::vector3df(0, 0, m_gunRotation));

	if (m_gravity > 0)
	{
		m_gunRotation += 600 * m_sharedContext->deltaTime;

		if (m_gunRotation > 180.f)
		{
			m_gunRotation = 180.f;
		}
	}
	else
	{
		m_gunRotation -= 600 * m_sharedContext->deltaTime;

		if (m_gunRotation < 0.f)
		{
			m_gunRotation = 0.f;
		}
	}

	m_animatedMeshComp->setRotation(m_animatedMeshComp->getRotation() + irr::core::vector3df(0, 0, m_gunRotation));
}

void Player::Reverse()
{
	if (m_gravityTimer >= 1.f)
	{
		m_gravityTimer = 0.f;
		m_gravity *= -1;
		m_collisionResponse->setGravity(irr::core::vector3df(0, m_gravity, 0));
	}
}
