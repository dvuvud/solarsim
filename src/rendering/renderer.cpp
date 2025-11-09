#include "renderer.hpp"

void Renderer::render(const Camera &camera) {
	for (auto& [shader, entities] : renderBatches) {
		shader->bind();
		for (auto* entity : entities) {
			entity->render(*shader);
		}
	}

}

void Renderer::clearAllEntities() {
	renderBatches.clear();
}

void Renderer::registerEntity(Entity& entity) {
	Shader* shader = entity.getMaterial()->shader;
	renderBatches[shader].push_back(&entity);
}
