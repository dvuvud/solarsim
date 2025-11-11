#include <simulation/planet.hpp>
#include <mesh/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Planet::Planet(Mesh* mesh, Material* material, const glm::vec3& position)
		: Entity(Transform{.position=position}, mesh, material)
		{

		}

	void Planet::update(float deltaTime)
	{
		// TODO: Implement planet specific update logic
	}

	void Planet::render(const Camera& p_camera)
	{
		Shader* shader = m_material->m_shader;
		if (!shader) return;
		shader->bind();
		shader->setMat4("view", p_camera.getViewMatrix());
		shader->setMat4("projection", p_camera.getProjectionMatrix());
		shader->setMat4("model", m_transform.getModelMatrix());

		shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		if (!m_mesh || !m_material) return;

		m_mesh->render();
	}
}
