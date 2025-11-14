#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/material.hpp>
#include <graphics/grid.hpp>
#include <simulation/simulation.hpp>
#include <mesh/mesh.hpp>
#include <simulation/entity.hpp>
#include <simulation/sun.hpp>
#include <iostream>

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
		draw_sun(p_sim->getSun(), camera);
		draw_entities(p_sim, camera);
		draw_grid(p_sim->getGrid(), camera);
	}

	void Renderer::draw_entities(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const
	{
		const std::vector<std::unique_ptr<Entity>>& entities = p_sim->getEntities();
		for (auto& entity : entities) {
			if (!entity || !p_camera) return;
			const Material& material = entity->getMaterial();
			const Mesh& mesh = entity->getMesh();
			const Shader& shader = material.m_shader;
			shader.bind();
			shader.setMat4("view", p_camera->getViewMatrix());
			shader.setMat4("projection", p_camera->getProjectionMatrix());
			shader.setMat4("model", entity->getTransform().getModelMatrix());

			shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

			const Sun* sun = p_sim->getSun();
			if (sun) {
				shader.setVec3("lightColor", glm::vec3(1.f, 1.f, 1.f));
				shader.setVec3("lightPos", sun->getPosition());
			} else {
				shader.setVec3("lightColor", glm::vec3(0.f, 0.f, 0.f));
				shader.setVec3("lightPos", glm::vec3(0.f,0.f,0.f));
			}	
				

			shader.setVec3("viewPos", p_camera->getPosition());

			mesh.render();
		}
	}

	void Renderer::draw_sun(const Sun* p_sun, const Camera* p_camera) const {
		if (!p_sun || !p_camera) return;
		const Shader& shader = p_sun->getMaterial().m_shader;
		const Mesh& mesh = p_sun->getMesh();
		shader.bind();
		shader.setMat4("uMVP", p_camera->getProjectionMatrix() * p_camera->getViewMatrix() * p_sun->getTransform().getModelMatrix());
		mesh.render();
	}

	void Renderer::draw_grid(const Grid* p_grid, const Camera* p_camera) const {
		if (!p_grid || !p_camera) return;
		glm::mat4 uMVP = p_camera->getProjectionMatrix() * p_camera->getViewMatrix();
		p_grid->draw(uMVP);
	}
}
