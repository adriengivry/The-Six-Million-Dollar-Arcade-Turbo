#include "Scene.h"
#include "EventManager.h"

Scene::Scene(SharedContext* p_sharedContext) : 
	m_sharedContext(p_sharedContext),
	m_sceneManager(*m_sharedContext->sceneManager)
{}

void Scene::InitScene()
{
	irr::scene::IMeshSceneNode* cube =         // pointeur vers le node
		m_sceneManager.addCubeSceneNode(        // la creation du cube
			10.0f,                             // cote de 10 unites
			0,                                 // parent = racine
			-1,                                // pas d'ID
			irr::core::vector3df(              // le vecteur de position
				0.0f,                          // origine en X
				0.0f,                          // origine en Y
				20.0f));                       // +20 unites en Z

	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);


	m_sceneManager.addCameraSceneNodeFPS(       // ajout de la camera FPS
		0,                                     // pas de noeud parent
		100.0f,                                // vitesse de rotation
		0.1f,                                  // vitesse de deplacement
		-1,
		m_sharedContext->eventManager->GetKeyMap("FPS_CAMERA"),
		5);                                    // avec une taille de 5
}
