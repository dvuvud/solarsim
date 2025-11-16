#include <memory>
#include <simulation/simulation.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>
#include <simulation/entity.hpp>
#include <iostream>

namespace solarsim {
	Simulation::Simulation() : m_camera(glm::vec3(0.f,2.f,50.f)), m_grid()
	{

	}
	Simulation::~Simulation() 
	{

	}

	void Simulation::spawnEntity(std::unique_ptr<Entity> p_entity) 
	{
		if (!p_entity) return;
		if (Sun* s = dynamic_cast<Sun*>(p_entity.get())) {
			m_sun = s;
		} else if (Planet* p = dynamic_cast<Planet*>(p_entity.get())) {
			m_planets.push_back(p);
		}
		m_entities.push_back(std::move(p_entity));
	}
	
	void Simulation::update(float deltaTime) 
	{
		deltaTime = isReversing ? -deltaTime : deltaTime;
		// TODO: Time complexity of force calculation is currently O(n^2)
		// Might improve this if I ever increase the same of the simulation
		calculateGravityForces();

		for (auto& entity : m_entities) {
			entity->update(deltaTime);
		}
	}

	void Simulation::calculateGravityForces() {
		const float G = .5f; // Arbitrary value for the gravitational constant (TODO: Make member var)
		const float MIN_DISTANCE = 1.5f; // Clamping distance and force to avoid extreme values
		
		for (size_t i = 0; i < m_entities.size(); ++i) {
			for (size_t j = i + 1; j < m_entities.size(); ++j) {
				auto& entityA = m_entities[i];
				auto& entityB = m_entities[j];
				glm::vec3 direction = entityB->getPosition() - entityA->getPosition();
				float distance = glm::length(direction);
				
				if (distance < MIN_DISTANCE) continue;

				direction = glm::normalize(direction);

				// Newton's law of universal gravitation: F = G * (m1 * m2) / r^2
				float forceMagnitude = G * (entityA->getMass() * entityB->getMass()) / (distance * distance);

				glm::vec3 force = direction * forceMagnitude;
				entityA->applyForce(force);
				entityB->applyForce(-force);
			}
		}
	}

	void Simulation::clearAllEntities() 
	{
		for (auto& entity : m_entities) {
			entity.reset();
		}
	}
}
