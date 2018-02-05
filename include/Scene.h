#pragma once
#include "SharedContext.h"
#include <ISceneManager.h>

class Scene
{
public:
	explicit Scene(SharedContext* p_sharedContext);
	~Scene() = default;

	irr::scene::ISceneManager& GetSceneManager() const { return m_sceneManager; }

	void InitScene();
private:
	SharedContext*				m_sharedContext;
	irr::scene::ISceneManager&	m_sceneManager;
};
