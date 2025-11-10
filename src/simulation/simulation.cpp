#include <simulation/simulation.hpp>

void Simulation::spawnEntity(std::unique_ptr<Entity> entity) {
	if (!entity) return;
	entities.push_back(std::move(entity));
}

void Simulation::update(float deltaTime) {
	// Apply physics
	for (auto& entity : entities) {
		entity->update(deltaTime);
	}
}

void Simulation::clearAllEntities() {
	entities.clear();
}
