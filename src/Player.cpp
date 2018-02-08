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
	m_cameraComponent = sceneManager.addCameraSceneNodeFPS(m_root, 100.f, 0.3f, -1, 0, 0, true, 4.f);
	m_cameraComponent->setPosition(irr::core::vector3df(50, 50, -60));
	m_cameraComponent->setTarget(irr::core::vector3df(-70, 30, -60));

	// Camera Animator
	m_cameraAnimator = static_cast<irr::scene::ISceneNodeAnimatorCameraFPS*>(*m_cameraComponent->getAnimators().begin());
	m_cameraAnimator->setKeyMap(fpsKeyMap, fpsKeyMapSize);
	m_cameraAnimator->setMoveSpeed(.3f);

	// Camera Collider
	m_collisionResponse = sceneManager.createCollisionResponseAnimator(nullptr, nullptr);
	m_collisionResponse->setTargetNode(m_cameraComponent);
	m_collisionResponse->setWorld(m_sharedContext->scene->GetWorld()->GetSelector());
	m_collisionResponse->setEllipsoidRadius(irr::core::vector3df(30, 50, 30));
	m_collisionResponse->setGravity(irr::core::vector3df(0, m_gravity, 0));
	m_cameraComponent->addAnimator(m_collisionResponse);

	// Animated FPS arms
	m_armsAndGun = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/gun.obj").c_str()), m_cameraComponent);
	m_armsAndGun->setRotation(irr::core::vector3df(0, 180, 0));
	m_armsAndGun->setPosition(irr::core::vector3df(5, 0, 15));

	// gun ray
	m_gunRay = sceneManager.addMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/ray.obj").c_str()), m_armsAndGun);
	m_gunRay->setRotation(irr::core::vector3df(0, 180, 0));
	m_gunRay->setPosition(irr::core::vector3df(0, 0, -7));
	m_gunRay->setScale(irr::core::vector3df(0.5f, 0.5f, 1));
	m_gunRay->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/textures/ray_texture.jpg"));
	auto gunLight = sceneManager.addLightSceneNode(m_gunRay, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1.f, 1.f, 0.3f));
}

void Player::Update()
{
	m_gravityTimer += m_sharedContext->deltaTime;

	m_shooting = m_sharedContext->eventManager->MouseLeftPressed();

	RotateGun();
	TranslateGun();
	UpdateRayLength();
	CheckDeath();

	m_gunRay->setVisible(m_shooting);
	m_gunRay->setScale(irr::core::vector3df(m_gunRay->getScale().X, m_gunRay->getScale().Y, m_rayLength));

	std::cout << m_collisionResponse->isFalling() << std::endl;
}

void Player::Reverse()
{
	if (m_gravityTimer >= 0.5f)
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
	m_armsAndGun->setRotation(m_armsAndGun->getRotation() - irr::core::vector3df(0, 0, m_gunRotation));

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

	m_armsAndGun->setRotation(m_armsAndGun->getRotation() + irr::core::vector3df(0, 0, m_gunRotation));
}

void Player::TranslateGun()
{
	m_armsAndGun->setPosition(m_armsAndGun->getPosition() - irr::core::vector3df(0, m_gunTranslation, 0));

	if (m_gravity > 0)
	{
		m_gunTranslation += 30.f * m_sharedContext->deltaTime;

		if (m_gunTranslation > 7.f)
		{
			m_gunTranslation = 7.f;
		}
	}
	else
	{
		m_gunTranslation -= 30.f * m_sharedContext->deltaTime;

		if (m_gunTranslation < -7.f)
		{
			m_gunTranslation = -7.f;
		}
	}

	m_armsAndGun->setPosition(m_armsAndGun->getPosition() + irr::core::vector3df(0, m_gunTranslation, 0));
}

void Player::UpdateRayLength()
{
	if (m_shooting)
	{
		m_rayLength += 500 * m_sharedContext->deltaTime;
		if (m_rayLength > 1000)
			m_rayLength = 1000;
	}
	else
	{
		m_rayLength = 0;
	}
}

void Player::CheckDeath()
{
	if (m_cameraComponent->getPosition().Y < PLAYER_MIN_Y_KILL || m_cameraComponent->getPosition().Y > PLAYER_MAX_Y_KILL)
	{
		exit(0);
	}
}
