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
		draw_sun(p_sim, camera);
		draw_planets(p_sim, camera);
		draw_grid(p_sim, camera);
	}

	void Renderer::draw_planets(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const
	{
		const std::vector<Planet*>& planets = p_sim->getPlanets();
		if (planets.empty() || !p_camera) return;
		for (auto& planet : planets) {
			if (!planet) continue;
			const Mesh* mesh = planet->getMesh();
			if (!mesh) continue;
			const Material* mat = planet->getMaterial();
			if (!mat) continue;
			const Shader* shader = mat->getShader();
			if (!shader) continue;

			shader->bind();
			shader->setMat4("view", p_camera->getViewMatrix());
			shader->setMat4("projection", p_camera->getProjectionMatrix());
			shader->setMat4("model", planet->getTransform().getModelMatrix());

			mat->apply();

			const std::vector<Sun*>& suns = p_sim->getSuns();
			std::vector<glm::vec3> lightPositions;
			std::vector<glm::vec3> lightColors;
			std::vector<float> lightRadii;
			int lightCount{0};
			for (auto& sun : suns) {
				if (sun) {
					++lightCount;
					lightPositions.push_back(sun->getPosition());
					lightColors.push_back(sun->getLightColor());
					lightRadii.push_back(sun->getLightRadius());
				}
			}
			shader->setVec3Array("uLightPositions", lightPositions);
			shader->setVec3Array("uLightColors", lightColors); 
			shader->setFloatArray("uLightRadii", lightRadii); // Determines at what distance the light fades completely
			shader->setInt("uLightCount", lightCount);

			shader->setVec3("viewPos", p_camera->getPosition());
			mesh->render();
		}
	}

	void Renderer::draw_sun(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const {
		const std::vector<Sun*>& suns = p_sim->getSuns();
		if (suns.empty() || !p_camera) return;
		for (auto& sun : suns) {
			if (!sun) continue;
			const Mesh* mesh = sun->getMesh();
			if (!mesh) continue;
			const Material* mat = sun->getMaterial();
			if (!mat) continue;
			const Shader* shader = mat->getShader();
			if (!shader) continue;
			shader->bind();
			shader->setMat4("uMVP", p_camera->getProjectionMatrix() * p_camera->getViewMatrix() * sun->getTransform().getModelMatrix());
			shader->setVec3("uLightColor", sun->getLightColor());
			mesh->render();
		}
	}

	void Renderer::draw_grid(const std::unique_ptr<Simulation>& p_sim, const Camera* p_camera) const {
		const Grid* grid = p_sim->getGrid();
		if (!grid || !p_camera) return;

		const Shader* shader = grid->getShader();

		shader->bind();

		glm::mat4 uVP = p_camera->getProjectionMatrix() * p_camera->getViewMatrix();
		shader->setMat4("uVP", uVP);

		const auto& entities = p_sim->getEntities();
		std::vector<glm::vec4> entityData;
		for (const auto& entity : entities) {
			glm::vec3 pos = entity->getPosition();
			entityData.push_back(glm::vec4(pos.x, pos.y, pos.z, entity->getMass()));
		}
		shader->setVec4Array("uEntities", entityData);
		shader->setInt("uEntityCount", (int)entities.size());

		const std::vector<Sun*>& suns = p_sim->getSuns();
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;
		std::vector<float> lightRadii;
		int lightCount{0};
		for (auto& sun : suns) {
			if (sun) {
				++lightCount;
				lightPositions.push_back(sun->getPosition());
				lightColors.push_back(sun->getLightColor());
				lightRadii.push_back(sun->getLightRadius());
			}
		}
		shader->setVec3Array("uLightPositions", lightPositions);
		shader->setVec3Array("uLightColors", lightColors); 
		shader->setFloatArray("uLightRadii", lightRadii); // Determines at what distance the light fades completely
		shader->setInt("uLightCount", lightCount);

		grid->draw();
	}
}
