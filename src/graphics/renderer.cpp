#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Renderer::Renderer(const std::vector<Entity*>& entities, Camera* camera) : entities(entities), activeCamera(camera)
	{
		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Renderer::render()
	{
		if (!activeCamera) return;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& entity : entities) {
			Shader* shader = entity->getMaterial()->shader;
			shader->bind();
			shader->setMat4("view", activeCamera->GetViewMatrix());
			shader->setMat4("projection", activeCamera->GetProjectionMatrix());
			entity->render(*shader); // Sets model matrix and draws
		}
	}
}
