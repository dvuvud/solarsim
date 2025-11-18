#pragma once

#include <graphics/camera.hpp>
#include <memory>
#include <graphics/grid.hpp>

namespace solarsim {
	class Entity;
	class Planet;
	class Sun;
	class Simulation {
		public:
			Simulation(bool shouldMakeGrid = true);
			~Simulation();

			void spawnEntity(std::unique_ptr<Entity> p_entity);

			void update(float deltaTime);

			void calculateGravityForces();

			void clearAllEntities();

			const Grid* getGrid() const { return m_grid.get(); }
			size_t getEntityCount() const { return m_entities.size(); };

			// TODO: Make this function const and add functionality for the input manager to handle input will less coupling
			Camera* getCamera() { return m_camera.get(); }
			const Camera* getCamera() const { return m_camera.get(); }
			const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
			const std::vector<Planet*>& getPlanets() const { return m_planets; }
			const std::vector<Sun*>& getSuns() const { return m_suns; }
			void toggleReverse() { isReversing = !isReversing; }
		private:
			std::unique_ptr<Grid> m_grid;
			// Entities are currently synonymous with planets, should be changed later both for clarity and functionality
			std::vector<std::unique_ptr<Entity>> m_entities;
			std::vector<Planet*> m_planets;
			std::vector<Sun*> m_suns;
			std::unique_ptr<Camera> m_camera;
			bool isReversing = false;

			// TODO: Implement physics system
			// PhysicsSystem physicsSystem;

	};
}
