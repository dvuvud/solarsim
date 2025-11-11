#include <simulation/simulation.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Simulation::Simulation() : m_camera(glm::vec3(0.f,0.f,5.f))
	{

	}
	Simulation::~Simulation() 
	{

	}

	void Simulation::spawnEntity(Entity* p_entity) 
	{
		if (!p_entity) return;
		m_entities.push_back(std::move(p_entity));
	}

	void Simulation::update(float deltaTime) 
	{
		// Apply physics
		for (Entity* entity : m_entities) {
			entity->update(deltaTime);
		}
	}

	void Simulation::clearAllEntities() 
	{
		m_entities.clear();
	}
}
