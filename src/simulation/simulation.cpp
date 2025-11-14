#include <memory>
#include <simulation/simulation.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Simulation::Simulation() : m_camera(glm::vec3(0.f,2.f,10.f)), m_grid()
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
		m_grid.update(*this);
	}

	void Simulation::clearAllEntities() 
	{
		m_entities.clear();
	}
}
