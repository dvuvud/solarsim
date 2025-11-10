#include "glad/glad.h"
#include <graphics/renderer.hpp>

Renderer::Renderer(std::vector<std::unique_ptr<Entity>>& entities, const Camera* camera) : entities(entities), activeCamera(camera)
{
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::render()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& entity : entities) {
		Shader* shader = entity->getMaterial()->shader;
		shader->bind();
		shader->setMat4("view", activeCamera->GetViewMatrix());
		shader->setMat4("projection", activeCamera->GetProjectionMatrix());
		entity->render(*shader);
	}

}
