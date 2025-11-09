#include "simulation.hpp"

void Simulation::spawnEntity(std::unique_ptr<Entity> entity) {
	if (!entity) return;

	Entity& entityRef = *entity;

	entities.push_back(std::move(entity));
	renderer.registerEntity(entityRef);
}

void Simulation::update(float deltaTime) {
	// Apply physics

	for (auto& entity : entities) {
		entity->update(deltaTime);
	}
}

void Simulation::render() {
	renderer.render(camera);
}

void Simulation::clearAllEntities() {
	renderer.clearAllEntities();

	// Physics system clear entities

	entities.clear();
}
