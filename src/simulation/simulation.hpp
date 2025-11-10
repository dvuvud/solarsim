#pragma once

#include "../rendering/renderer.hpp"
#include "../core/camera.hpp"
#include "../core/input_manager.hpp"
#include "../core/window.hpp"
#include "entity.hpp"

class Simulation {
	public:
		Simulation()
			: camera(glm::vec3(0.f, 0.f, 5.f)),
			renderer(entities) {};
		~Simulation() = default;

		void spawnEntity(std::unique_ptr<Entity> entity);

		void update(float deltaTime);        


		void render();

		void clearAllEntities();

		size_t getEntityCount() const { return entities.size(); };
		Camera* getCamera() { return &camera; }
	private:
		std::vector<std::unique_ptr<Entity>> entities;

		Renderer renderer;
		Camera camera;

		// TODO: Implement physics system
		// PhysicsSystem physicsSystem;

};
