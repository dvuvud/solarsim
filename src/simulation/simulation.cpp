#include <simulation/simulation.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Simulation::~Simulation() {
		for (Entity* entity: entities) {
			delete entity;
		}
	}

	void Simulation::spawnEntity(Entity* entity) {
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
}
