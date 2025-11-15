#pragma once

#include <graphics/camera.hpp>
#include <memory>
#include <graphics/grid.hpp>
#include <sys/wait.h>

namespace solarsim {
	class Entity;
	class Planet;
	class Sun;
	class Simulation {
		public:
			Simulation();
			~Simulation();

			void spawnEntity(std::unique_ptr<Entity> p_entity);

			void update(float deltaTime);

			void calculateGravityForces();

			void clearAllEntities();

			const Grid* getGrid() const { return &m_grid; }
			size_t getEntityCount() const { return m_entities.size(); };

			// TODO: Make this function const and add functionality for the input manager to handle input will less coupling
			Camera* getCamera() { return &m_camera; }
			const Camera* getCamera() const { return &m_camera; }
			const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
			const std::vector<Planet*>& getPlanets() const { return m_planets; }
			const Sun* getSun() const { return m_sun; }
			void toggleReverse() { isReversing = !isReversing; }
		private:
			Grid m_grid;
			// Entities are currently synonymous with planets, should be changed later both for clarity and functionality
			std::vector<std::unique_ptr<Entity>> m_entities;
			std::vector<Planet*> m_planets;
			Sun* m_sun;
			Camera m_camera;
			bool isReversing;

			// TODO: Implement physics system
			// PhysicsSystem physicsSystem;

	};
}
