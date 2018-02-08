#pragma once
#include "SharedContext.h"
#include <ISceneManager.h>
#include "Terrain.h"
#include "Skybox.h"

class Player;

class Scene
{
public:
	explicit Scene(SharedContext* p_sharedContext);
	~Scene() = default;

	irr::scene::ISceneManager&	GetSceneManager()	const { return m_sceneManager; }
	Terrain*					GetTerrain()		const { return m_terrain; }
	Skybox*						GetSkybox()			const { return m_skybox; }
	Player*						GetPlayer()			const { return m_player; }

	void InitScene();
	void Update();
private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneManager&	m_sceneManager;

	Player*		m_player;
	Terrain*	m_terrain;
	Skybox*		m_skybox;
};
