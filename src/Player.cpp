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
	m_cameraComponent = sceneManager.addCameraSceneNodeFPS(m_root);
	m_cameraComponent->setPosition(irr::core::vector3df(50, 50, -60));
	m_cameraComponent->setTarget(irr::core::vector3df(-70, 30, -60));

	// Camera Animator
	m_cameraAnimator = static_cast<irr::scene::ISceneNodeAnimatorCameraFPS*>(*m_cameraComponent->getAnimators().begin());
	m_cameraAnimator->setKeyMap(fpsKeyMap, fpsKeyMapSize);
	m_cameraAnimator->setVerticalMovement(false);
	m_cameraAnimator->setMoveSpeed(.3f);

	// Camera Collider
	m_collisionResponse = sceneManager.createCollisionResponseAnimator(m_sharedContext->scene->GetWorld()->GetSelector(), m_cameraComponent);
	m_collisionResponse->setEllipsoidRadius(irr::core::vector3df(30, 50, 30));
	m_collisionResponse->setGravity(irr::core::vector3df(0, m_gravity, 0));
	m_cameraComponent->addAnimator(m_collisionResponse);

	// Animated FPS arms
	m_armsAndGun = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/gun.obj").c_str()), m_cameraComponent);
	m_armsAndGun->setRotation(irr::core::vector3df(0, 180, 0));
	m_armsAndGun->setPosition(irr::core::vector3df(7, -10, 20));

	const irr::core::vector3df gunExitPoint(8, -11, 30);

	// gun ray
	m_gunRay = sceneManager.addMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/ray.obj").c_str()), m_armsAndGun);
	m_gunRay->setRotation(irr::core::vector3df(0, 180, 0));
	m_gunRay->setPosition(irr::core::vector3df(0, 0, -7));
	m_gunRay->setScale(irr::core::vector3df(0.5f, 0.5f, 1));
	m_gunRay->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/meshes/purmesh.jpg"));

	// Gun ray particules
	m_particleSystem = sceneManager.addParticleSystemSceneNode(false , m_cameraComponent);

	m_emitter = m_particleSystem->createCylinderEmitter(irr::core::vector3df(0, 0, 0), 5, irr::core::vector3df(0, 0, 1), 0);
	m_emitter->setMinLifeTime(200);
	m_emitter->setMaxLifeTime(300);
	m_emitter->setMinParticlesPerSecond(500);
	m_emitter->setMaxParticlesPerSecond(500);
	m_emitter->setMinStartSize(irr::core::dimension2df(1.f, 1.f));
	m_emitter->setMaxStartSize(irr::core::dimension2df(3.f, 3.f));

	irr::scene::IParticleAffector* affectorFadeOut = m_particleSystem->createFadeOutParticleAffector();
	irr::scene::IParticleAffector* affectorGravity = m_particleSystem->createGravityAffector(irr::core::vector3df(0, -0.25f, 0));

	m_particleSystem->setEmitter(m_emitter);
	m_particleSystem->setPosition(gunExitPoint);
	m_particleSystem->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/textures/fire.png"));
	m_particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);

	m_particleSystem->addAffector(affectorFadeOut);
	m_particleSystem->addAffector(affectorGravity);

	affectorFadeOut->drop();
	affectorGravity->drop();
}

void Player::Update()
{
	m_gravityTimer += m_sharedContext->deltaTime;

	RotateGun();
	HandleEvents();

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

	m_emitter->setLength(m_rayLength);
	m_gunRay->setScale(irr::core::vector3df(m_gunRay->getScale().X, m_gunRay->getScale().Y, m_rayLength));
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

void Player::HandleEvents()
{
	m_shooting = m_sharedContext->eventManager->MouseLeftPressed();

	m_gunRay->setVisible(m_shooting);
	m_particleSystem->setVisible(m_shooting);

	if (!m_shooting)
	{
		m_particleSystem->clearParticles();
	}
}
