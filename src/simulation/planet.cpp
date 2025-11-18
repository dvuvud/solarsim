#include <simulation/planet.hpp>
#include <mesh/cube.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <memory>
#include <iostream>

namespace solarsim {
	Planet::Planet(const Transform& transform, float m, float r, const glm::vec3& iv, const glm::vec3& c)
		: Entity(transform, m, r), m_color(c)
	{
		this->setVelocity(iv);
	}

	Planet::Planet(const Transform& transform, std::unique_ptr<Mesh>& p_mesh, std::unique_ptr<Material>& p_mat, float m, float r, const glm::vec3& iv, const glm::vec3& c)
		: Entity(transform, p_mesh, p_mat, m, r), m_color(c)
	{
		this->setVelocity(iv);
	}

	void Planet::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
