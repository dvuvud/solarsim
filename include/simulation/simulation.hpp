#pragma once

#include <graphics/camera.hpp>
#include <memory>
#include <graphics/grid.hpp>
#include <sys/wait.h>

namespace solarsim {
	class Entity;
	class Sun;
	class Simulation {
		public:
			Simulation();
			~Simulation();

			void spawnEntity(std::unique_ptr<Entity> p_entity);
			void spawnSun(std::unique_ptr<Sun> p_sun);

			void update(float deltaTime);        

			void clearAllEntities();

			const Grid* getGrid() const { return &m_grid; }
			size_t getEntityCount() const { return m_entities.size(); };
			// TODO: Make this function const and add API calls for the input manager to handle input
			Camera* getCamera() { return &m_camera; }
			const Camera* getCamera() const { return &m_camera; }
			const std::vector<std::unique_ptr<Entity>>& getEntities() const { return m_entities; }
			const Sun* getSun() const { return m_sun.get(); }
		private:
			Grid m_grid;
			std::vector<std::unique_ptr<Entity>> m_entities;
			std::unique_ptr<Sun> m_sun;
			Camera m_camera;

			// TODO: Implement physics system
			// PhysicsSystem physicsSystem;

	};
}
