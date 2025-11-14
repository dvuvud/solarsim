#include <simulation/planet.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Planet::Planet(const glm::vec3& position, float m, float r)
		: m_material("assets/shaders/planet.vert", "assets/shaders/planet.frag"),
		Entity(Transform{.position=position}, m_mesh, m_material, m, r)
		{
			this->setVelocity(glm::vec3(0.5, 0.f, 0.f)); // Initial velocity
		}

	void Planet::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
