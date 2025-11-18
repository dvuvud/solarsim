#include <memory>
#include <simulation/simulation.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>
#include <simulation/entity.hpp>
#include <iostream>

namespace solarsim {
	Simulation::Simulation(bool shouldMakeGrid) 
		: m_camera(std::make_unique<Camera>(glm::vec3(0.f,2.f,50.f)))
	{
		if (shouldMakeGrid) m_grid = std::make_unique<Grid>();
	}
	Simulation::~Simulation() 
	{

	}

	void Simulation::spawnEntity(std::unique_ptr<Entity> p_entity) 
	{
		if (!p_entity) return;
		if (Sun* s = dynamic_cast<Sun*>(p_entity.get())) {
			m_suns.push_back(s);
		} else if (Planet* p = dynamic_cast<Planet*>(p_entity.get())) {
			m_planets.push_back(p);
		}
		m_entities.push_back(std::move(p_entity));
	}

	void Simulation::update(float deltaTime) 
	{
		deltaTime = isReversing ? -deltaTime : deltaTime;
		calculateGravityForces();

		for (auto& entity : m_entities) {
			entity->update(deltaTime);
		}
	}

	void Simulation::calculateGravityForces() {
		for (size_t i = 0; i < m_entities.size(); ++i) {
			for (size_t j = i + 1; j < m_entities.size(); ++j) {
				auto& entityA = m_entities[i];
				auto& entityB = m_entities[j];
				glm::vec3 direction = entityB->getPosition() - entityA->getPosition();
				float distanceSquared = glm::dot(direction, direction);

				float softenedDistanceSquared = distanceSquared + SOFTENING_SQUARED;

				direction = glm::normalize(direction);

				// Newton's law of universal gravitation: F = G * (m1 * m2) / r^2
				float forceMagnitude = G * (entityA->getMass() * entityB->getMass()) / (softenedDistanceSquared);

				glm::vec3 force = direction * forceMagnitude;
				entityA->applyForce(force);
				entityB->applyForce(-force);
			}
		}
	}

	void Simulation::clearAllEntities() 
	{
		m_entities.clear();
		m_planets.clear();
		m_suns.clear();
	}
}
