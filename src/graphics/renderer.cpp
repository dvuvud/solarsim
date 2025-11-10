#include "glad/glad.h"
#include <graphics/renderer.hpp>

Renderer::Renderer(std::vector<std::unique_ptr<Entity>>& entities) : entities(entities) {
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::render(const Camera &camera) {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& entity : entities) {
		Shader* shader = entity->getMaterial()->shader;
		shader->bind();
		shader->setMat4("view", camera.GetViewMatrix());
		shader->setMat4("projection", camera.GetProjectionMatrix());
		entity->render(*shader);
	}

}
