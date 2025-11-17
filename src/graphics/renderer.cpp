#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/material.hpp>
#include <graphics/grid.hpp>
#include <simulation/simulation.hpp>
#include <mesh/mesh.hpp>
#include <simulation/planet.hpp>
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
		draw_planets(p_sim, camera);
		draw_grid(p_sim, camera);
	}

	void Renderer::draw_planets(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const
	{
		const std::vector<Planet*>& planets = p_sim->getPlanets();
		for (auto& planet : planets) {
			if (!planet || !p_camera) return;
			const Mesh* mesh = planet->getMesh();
			if (!mesh) return;
			const Material* mat = planet->getMaterial();
			if (!mat) return;
			const Shader* shader = mat->getShader();
			if (!shader) return;

			shader->bind();
			shader->setMat4("view", p_camera->getViewMatrix());
			shader->setMat4("projection", p_camera->getProjectionMatrix());
			shader->setMat4("model", planet->getTransform().getModelMatrix());

			// TODO: Make this a member variable on planets/materials
			shader->setVec3("objectColor", glm::vec3(0.15f, 0.175f, 0.925f));

			// TODO: After multiple light sources are made possible, add functionality for handling no light being present
			if (const Sun* s = p_sim->getSun()) {
				shader->setVec3("lightColor", s->getLightColor());
				shader->setVec3("lightPos", s->getPosition());
			}

			shader->setVec3("viewPos", p_camera->getPosition());
			mesh->render();
		}
	}

	void Renderer::draw_sun(const Sun* p_sun, const Camera* p_camera) const {
		if (!p_sun || !p_camera) return;
		const Mesh* mesh = p_sun->getMesh();
		if (!mesh) return;
		const Material* mat = p_sun->getMaterial();
		if (!mat) return;
		const Shader* shader = mat->getShader();
		if (!shader) return;
		shader->bind();
		shader->setMat4("uMVP", p_camera->getProjectionMatrix() * p_camera->getViewMatrix() * p_sun->getTransform().getModelMatrix());
		shader->setVec3("uLightColor", p_sun->getLightColor());
		mesh->render();
	}

	void Renderer::draw_grid(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const {
		const Grid* grid = p_sim->getGrid();
		if (!grid || !p_camera) return;

		const Shader& shader = grid->getShader();

		shader.bind();

		glm::mat4 uVP = p_camera->getProjectionMatrix() * p_camera->getViewMatrix();
		shader.setMat4("uVP", uVP);

		const auto& entities = p_sim->getEntities();
		std::vector<glm::vec4> entityData;
		for (const auto& entity : entities) {
			glm::vec3 pos = entity->getPosition();
			entityData.push_back(glm::vec4(pos.x, pos.y, pos.z, entity->getMass()));
		}
		shader.setVec4Array("uEntities", entityData);
		shader.setInt("uEntityCount", (int)entities.size());

		const Sun* sun = p_sim->getSun();
		if (sun) {
			shader.setVec3("uLightPos", sun->getPosition());
			shader.setVec3("uLightColor", sun->getLightColor());
			shader.setFloat("uLightRadius", sun->getLightRadius()); // Determines at what distance the light fades completely
		}

		grid->draw();
	}
}
