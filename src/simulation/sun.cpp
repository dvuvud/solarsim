#include <simulation/sun.hpp>
#include <mesh/cube.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <memory>
#include <iostream>

namespace solarsim {
	Sun::Sun(const Transform& transform, float m, float r, float lr, const glm::vec3& lc, const glm::vec3& iv)
		: Entity(transform, m, r), m_lightRadius(lr), m_lightColor(lc)
	{
		this->setVelocity(iv);
	}
	Sun::Sun(const Transform& transform,
					std::unique_ptr<Mesh>& p_mesh,
					std::unique_ptr<Material>& p_mat,
					float m,
					float r,
					float lr,
					const glm::vec3& lc,
					const glm::vec3& iv)
		: Entity(transform, p_mesh, p_mat, m, r), m_lightRadius(lr), m_lightColor(lc)
	{
		this->setVelocity(iv);
	}

	void Sun::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
