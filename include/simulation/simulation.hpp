#pragma once

#include <graphics/camera.hpp>
#include <memory>

namespace solarsim {
	class Entity;
	class Simulation {
		public:
			Simulation() : camera(glm::vec3(0.f, 0.f, 5.f)) {};
			~Simulation();

			void spawnEntity(Entity* entity);

			void update(float deltaTime);        

			void clearAllEntities();

			size_t getEntityCount() const { return entities.size(); };
			Camera* getCamera() { return &camera; }
			const std::vector<Entity*>& getEntities() const { return entities; }
		private:
			std::vector<Entity*> entities;
			Camera camera;

			// TODO: Implement physics system
			// PhysicsSystem physicsSystem;

	};
}
