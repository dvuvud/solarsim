#pragma once

#include <graphics/camera.hpp>
#include <memory>

namespace solarsim {
	class Entity;
	class Simulation {
		public:
			Simulation();
			~Simulation();

			void spawnEntity(Entity* p_entity);

			void update(float deltaTime);        

			void clearAllEntities();

			size_t getEntityCount() const { return m_entities.size(); };
			Camera* getCamera() { return &m_camera; }
			const std::vector<Entity*>& getEntities() const { return m_entities; }
		private:
			std::vector<Entity*> m_entities;
			Camera m_camera;

			// TODO: Implement physics system
			// PhysicsSystem physicsSystem;

	};
}
