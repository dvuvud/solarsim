#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <mesh/mesh.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Renderer::Renderer()
	{
		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Renderer::render(const std::vector<std::unique_ptr<Entity>>& p_entities, const Camera* p_camera) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!p_camera) return;
		for (auto& entity : p_entities) {
			Material* material = entity ? entity->getMaterial() : nullptr;
			Shader* shader = material ? material->m_shader : nullptr;
			Mesh* mesh = shader ? entity->getMesh() : nullptr;
			if (!mesh) return;
			shader->bind();
			shader->setMat4("view", p_camera->getViewMatrix());
			shader->setMat4("projection", p_camera->getProjectionMatrix());
			shader->setMat4("model", entity->getTransform().getModelMatrix());

			shader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
			shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
			shader->setVec3("lightPos", glm::vec3(3.f,3.f,-5.f));
			shader->setVec3("viewPos", p_camera->getPosition());
			mesh->render();
		}
	}
}
