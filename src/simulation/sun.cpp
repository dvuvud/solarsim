#include <simulation/sun.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Sun::Sun(const glm::vec3& position, float m, float r)
		: m_material("assets/shaders/sun.vert", "assets/shaders/sun.frag"),
		Entity(Transform{.position=position}, m_mesh, m_material, m, r)
		{

		}

	void Sun::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
