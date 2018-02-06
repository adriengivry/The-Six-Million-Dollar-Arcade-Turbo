#include "Player.h"
#include "EventManager.h"
#include "Scene.h"
#include "Utilities.h"
#include "Window.h"

Player::Player(SharedContext* p_sharedContext)
{
	m_sharedContext = p_sharedContext;

	InitComponents();
}

Player::~Player()
{
}

void Player::InitComponents()
{
	SceneManager& sceneManager = m_sharedContext->scene->GetSceneManager();

	m_cameraComponent = sceneManager.addCameraSceneNodeFPS(
		nullptr, 100.0f, 0.3f, -1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		m_sharedContext->eventManager->GetKeyMapSize("FPS_CAMERA"), true, 1.f);
	irr::scene::ISceneNodeAnimator* anim = sceneManager.createCollisionResponseAnimator(
		m_sharedContext->scene->GetWorld()->GetSelector(), m_cameraComponent, irr::core::vector3df(30, 50, 30),
		irr::core::vector3df(0, -1, 0), irr::core::vector3df(0, 30, 0));
	m_cameraComponent->addAnimator(anim);
	anim->drop();  // And likewise, drop the animator when we're done referring to it.

	m_animatedMeshComp = sceneManager.addAnimatedMeshSceneNode(
		sceneManager.getMesh(Utils::LoadAsset("meshes/gun.md2").c_str()),
		m_cameraComponent);

	m_animatedMeshComp->setRotation(irr::core::vector3df(0, -90, 0));

	m_animatedMeshComp->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture(Utils::LoadAsset("textures/gun.jpg").c_str()));
}

void Player::Update()
{
	// BLOCK PLAYER Y WHEN WORLD IS ROTATING
	if (m_sharedContext->scene->GetWorld()->IsRotating())
		m_cameraComponent->setPosition(irr::core::vector3df(m_cameraComponent->getPosition().X, m_yPositionMemory, m_cameraComponent->getPosition().Z));
	else
		m_yPositionMemory = m_cameraComponent->getPosition().Y;
}
