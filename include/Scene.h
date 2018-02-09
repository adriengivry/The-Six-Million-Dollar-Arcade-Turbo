#pragma once
#include "SharedContext.h"
#include <ISceneManager.h>
#include "Terrain.h"
#include "Skybox.h"
#include <vector>
#include "Breakable.h"

class Player;

class Scene
{
public:
	explicit Scene(SharedContext* p_sharedContext);
	~Scene();

	irr::scene::ISceneManager&	GetSceneManager()	const { return m_sceneManager; }
	Terrain*					GetTerrain()		const { return m_terrain; }
	Skybox*						GetSkybox()			const { return m_skybox; }
	Player*						GetPlayer()			const { return m_player; }
	std::vector<Breakable*>&	GetBreakables()		{ return m_breakables; }

	irr::scene::IMetaTriangleSelector* GetWorldCollider() const { return m_worldCollider; }

	void InitScene();
	void Update();

	void AddBlock(irr::f32 p_x, irr::f32 p_y, irr::f32 p_z, irr::u16 p_blockSize = 50);
private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneManager&	m_sceneManager;

	Player*		m_player;
	Terrain*	m_terrain;
	Skybox*		m_skybox;

	std::vector<Breakable*> m_breakables;

	irr::scene::IMetaTriangleSelector* m_worldCollider;
};
