#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <graphics/grid.hpp>
#include <simulation/simulation.hpp>
#include <mesh/mesh.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Renderer::Renderer()
	{
		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Renderer::render(const std::unique_ptr<Simulation>& p_sim) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		const Camera* camera = p_sim->getCamera();
		if (!camera) return;
		const std::vector<std::unique_ptr<Entity>>& entities = p_sim->getEntities();
		for (auto& entity : entities) {
			draw_entity(entity, *camera);
		}
		draw_grid(p_sim->getGrid(), *camera);
	}

	void Renderer::draw_entity(const std::unique_ptr<Entity>& p_entity, const Camera& p_camera) const
	{
			const Material& material = p_entity->getMaterial();
			const Shader& shader = material.m_shader;
			const Mesh& mesh = p_entity->getMesh();
			shader.bind();
			shader.setMat4("view", p_camera.getViewMatrix());
			shader.setMat4("projection", p_camera.getProjectionMatrix());
			shader.setMat4("model", p_entity->getTransform().getModelMatrix());

			shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
			shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			
			// TODO: Give the renderer a pointer to the light source and create a new class for them
			shader.setVec3("lightPos", glm::vec3(0.f, 0.f, 0.f));
			shader.setVec3("viewPos", p_camera.getPosition());
			mesh.render();
	}

	void Renderer::draw_grid(const Grid& p_grid, const Camera& p_camera) const {
		glm::mat4 uMVP = p_camera.getProjectionMatrix() * p_camera.getViewMatrix();
		p_grid.draw(uMVP);
	}
}
