#pragma once

#include <graphics/renderer.hpp>
#include <graphics/camera.hpp>
#include <core/input_manager.hpp>
#include <core/window.hpp>
#include <simulation/entity.hpp>
#include <memory>

class Simulation {
	public:
		Simulation() : camera(glm::vec3(0.f, 0.f, 5.f)) {};
		~Simulation() = default;

		void spawnEntity(std::unique_ptr<Entity> entity);

		void update(float deltaTime);        

		void clearAllEntities();

		size_t getEntityCount() const { return entities.size(); };
		Camera* getCamera() { return &camera; }
		const std::vector<std::unique_ptr<Entity>>& getEntities() const { return entities; }
	private:
		std::vector<std::unique_ptr<Entity>> entities;
		Camera camera;

		// TODO: Implement physics system
		// PhysicsSystem physicsSystem;

};
