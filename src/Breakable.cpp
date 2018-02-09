#include "Breakable.h"
#include "Scene.h"
#include "Window.h"
#include <string>

Breakable::Breakable(SharedContext* p_sharedContext, const irr::core::vector3df& p_pos, irr::u16 p_blockSize)
{
	m_sharedContext = p_sharedContext;
	m_rotation = 0.f;
	m_scale = 1.f;
	m_cleanMePlease = false;
	m_breaking = false;

	std::string id = "BREAKABLE_" + std::to_string(m_sharedContext->breakableID++);
	
	m_node = m_sharedContext->scene->GetSceneManager().addCubeSceneNode(p_blockSize, nullptr, ID_Activable);
	m_node->setName(id.c_str());
	m_collider = m_sharedContext->scene->GetSceneManager().createTriangleSelector(m_node->getMesh(), m_node);
	m_node->setMaterialTexture(0, m_sharedContext->window->GetDriver()->getTexture("../assets/textures/breakable.png"));
	m_node->setTriangleSelector(m_collider);
	m_node->setPosition(p_pos);
}

void Breakable::Destroy()
{
	if (!m_breaking)
	{
		m_breaking = true;
		m_sharedContext->scene->GetWorldCollider()->removeTriangleSelector(m_collider);
	}
}

void Breakable::Update()
{
	if (m_breaking)
	{
		m_node->setRotation(m_node->getRotation() - irr::core::vector3df(0, 0, m_rotation));
		m_node->setScale(m_node->getScale() - m_scale);
		m_node->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

		m_rotation += 360.f * m_sharedContext->deltaTime;
		m_scale -= 1.f * m_sharedContext->deltaTime;

		if (m_rotation >= 360.f)
			m_rotation = 360.f;

		if (m_scale <= 0.f)
			m_scale = 0.f;

		if (m_rotation >= 360.f && m_scale <= 0.f)
		{
			m_cleanMePlease = true;
			m_breaking = false;
		}

		m_node->setScale(m_node->getScale() + m_scale);
		m_node->setRotation(m_node->getRotation() + irr::core::vector3df(0, 0, m_rotation));
	}

	if (m_cleanMePlease)
	{
		m_node->setVisible(false);
	}
}
