#include <simulation/planet.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Planet::Planet(const glm::vec3& position, float m, float p)
		: m_material("assets/shaders/planet.vert", "assets/shaders/planet.frag"),
		Entity(Transform{.position=position}, m_mesh, m_material)
		{

		}

	void Planet::update(float deltaTime)
	{
		// TODO: Implement planet specific update logic
	}
}
