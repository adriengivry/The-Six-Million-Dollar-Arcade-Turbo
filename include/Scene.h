#pragma once
#include "SharedContext.h"
#include <ISceneManager.h>
#include "World.h"

class Player;

class Scene
{
public:
	explicit Scene(SharedContext* p_sharedContext);
	~Scene() = default;

	irr::scene::ISceneManager& GetSceneManager() const { return m_sceneManager; }
	World* GetWorld() const { return m_world; }
	Player* GetPlayer() const { return m_player; }

	void InitScene();
	void Update();
private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneManager&	m_sceneManager;
	Player* m_player;
	World* m_world;
};
