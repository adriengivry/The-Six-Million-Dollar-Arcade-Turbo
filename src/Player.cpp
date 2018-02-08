#include "Player.h"
#include "EventManager.h"
#include "Scene.h"
#include "Utilities.h"
#include "Window.h"
#include <iostream>

Player::Player(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;
	m_gravity = -9.81;
	m_gunRotation = 0.f;
	m_mouseInverted = false;
	m_gravityTimer = 0.f;
	m_rayLength = 0.f;
	m_fallingTimer = 0.f;

	CreateCamera();
	CreateGun();
}

void Player::CreateCamera()
{
	SceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	irr::SKeyMap*	fpsKeyMap = m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA");
	const irr::s32	fpsKeyMapSize = m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA");

	// Camera Node
	m_cameraNode = sceneManager.addCameraSceneNodeFPS(nullptr, 100.f, 0.3f, -1, nullptr, 0, true, 4.f);
	m_cameraNode->setPosition(irr::core::vector3df(500, 100, 300));
	m_cameraNode->setTarget(irr::core::vector3df(-70, 30, -60));

	// Camera Animator
	m_cameraAnimator = static_cast<irr::scene::ISceneNodeAnimatorCameraFPS*>(*m_cameraNode->getAnimators().begin());
	m_cameraAnimator->setKeyMap(fpsKeyMap, fpsKeyMapSize);
	m_cameraAnimator->setMoveSpeed(.3f);

	// Camera Collider
	m_cameraCollider = sceneManager.createCollisionResponseAnimator(m_sharedContext->scene->GetTerrain()->GetCollider(), m_cameraNode);
	m_cameraCollider->setEllipsoidRadius(irr::core::vector3df(30, 60, 30));
	m_cameraCollider->setGravity(irr::core::vector3df(0, m_gravity, 0));
	m_cameraNode->addAnimator(m_cameraCollider);
}

void Player::CreateGun()
{
	SceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();
	
	// Gun Node
	m_gunNode = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/gun.obj").c_str()), m_cameraNode);
	m_gunNode->setRotation(irr::core::vector3df(0, 180, 0));
	m_gunNode->setPosition(irr::core::vector3df(5, 0, 15));
	m_gunNode->getMaterial(0).Shininess = 120.f;
	m_gunNode->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/textures/gun_map.png"));

	// Ray Node
	m_rayNode = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/ray.obj").c_str()), m_gunNode);
	m_rayNode->setRotation(irr::core::vector3df(0, 180, 0));
	m_rayNode->setPosition(irr::core::vector3df(0, 0, -7));
	m_rayNode->setScale(irr::core::vector3df(.5f, .5f, 1.f));
	m_rayNode->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/textures/ray_texture.jpg"));
	m_rayNode->getMaterial(0).EmissiveColor.set(255, 255, 255, 0);
	m_rayNode->setVisible(false);
	m_gunLightNode = sceneManager.addLightSceneNode(m_rayNode, irr::core::vector3df(0, 0, 0), irr::video::SColorf(1.f, 1.f, 1.f), 50);
}

void Player::Update()
{
	m_gravityTimer += m_sharedContext->deltaTime;

	if (m_cameraCollider->isFalling())
		m_fallingTimer += m_sharedContext->deltaTime;
	else
		m_fallingTimer = 0.f;

	UpdateGun();
	UpdateRay();

	CheckDeath();
}

void Player::UpdateGun()
{
	RotateGun();
	TranslateGun();
}

void Player::Reverse()
{
	if (m_gravityTimer >= 0.5f)
	{
		m_mouseInverted = !m_mouseInverted;
		m_gravityTimer = 0.f;
		m_gravity *= -1;
		m_cameraCollider->setGravity(irr::core::vector3df(0, m_gravity, 0));
		
		m_cameraNode->setUpVector(m_cameraNode->getUpVector() * -1);
		m_cameraAnimator->setInvertMouse(m_mouseInverted);
	}
}

void Player::RotateGun()
{
	m_gunNode->setRotation(m_gunNode->getRotation() - irr::core::vector3df(0, 0, m_gunRotation));

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

	m_gunNode->setRotation(m_gunNode->getRotation() + irr::core::vector3df(0, 0, m_gunRotation));
}

void Player::TranslateGun()
{
	m_gunNode->setPosition(m_gunNode->getPosition() - irr::core::vector3df(0, m_gunTranslation, 0));

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

	m_gunNode->setPosition(m_gunNode->getPosition() + irr::core::vector3df(0, m_gunTranslation, 0));
}

void Player::UpdateRayLength()
{
	if (IsShooting())
	{
		m_rayLength += 500 * m_sharedContext->deltaTime;
		if (m_rayLength > 1000)
			m_rayLength = 1000;
	}
	else
	{
		m_rayLength = 0;
	}

	m_rayNode->setScale(irr::core::vector3df(m_rayNode->getScale().X, m_rayNode->getScale().Y, m_rayLength));
}

void Player::UpdateRay()
{
	m_rayNode->setVisible(IsShooting());

	UpdateRayLength();
	UpdateRayCollider();
}

void Player::UpdateRayCollider()
{
	if (m_rayNode->isVisible())
	{
		irr::core::line3d<irr::f32> ray;
		ray.start = m_cameraNode->getPosition();
		ray.end = ray.start + (m_cameraNode->getTarget() - ray.start).normalize() * 1000.0f;

		irr::core::vector3df collisionPoint;
		irr::core::triangle3df outTriangle;

		irr::scene::ISceneNode * selectedSceneNode = m_sharedContext->scene->GetSceneManager().getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
			ray,
			collisionPoint,
			outTriangle,
			ID_Activable
			);

		if (selectedSceneNode)
		{
			selectedSceneNode->setVisible(false);
		}
	}
}

void Player::CheckDeath() const
{
	if (m_cameraNode->getPosition().Y < PLAYER_MIN_Y_KILL ||
		m_cameraNode->getPosition().Y > PLAYER_MAX_Y_KILL ||
		m_sharedContext->gameInfo.currentScore == 0)
	{
		exit(0);
	}
}

bool Player::IsShooting() const
{
	return m_sharedContext->eventManager->MouseLeftPressed();
}

bool Player::CanReverse() const
{
	return m_fallingTimer <= 0.1f;
}
