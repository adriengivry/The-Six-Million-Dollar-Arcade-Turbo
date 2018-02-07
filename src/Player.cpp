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
	m_animatedMeshComp = sceneManager.addAnimatedMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/gun.obj").c_str()), m_cameraComponent);
	m_animatedMeshComp->setRotation(irr::core::vector3df(0, 180, 0));
	m_animatedMeshComp->setPosition(irr::core::vector3df(7, -10, 20));

	const irr::core::vector3df gunExitPoint(8, -11, 30);

	// gun ray
	m_gunRay = sceneManager.addMeshSceneNode(sceneManager.getMesh(Utils::LoadAsset("meshes/ray.obj").c_str()), m_cameraComponent);
	m_gunRay->setPosition(gunExitPoint);
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

	m_gunLight = sceneManager.addLightSceneNode(m_gunRay, irr::core::vector3df(0, 0, 0),
		irr::video::SColorf(0.4f, 0.4f, 0.6f, 0.0f), 180.f);
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
	m_gunRay->setScale(irr::core::vector3df(1, 1, m_rayLength));
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

	if (!m_shooting)
	{
		m_particleSystem->clearParticles();
	}
}
