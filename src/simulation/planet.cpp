#include <simulation/planet.hpp>
#include <mesh/cube.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Planet::Planet(const Transform& transform, float m, float r)
		: Entity(transform,
				Cube(),
				Material("assets/shaders/planet.vert", "assets/shaders/planet.frag"),
				m,
				r)
	{
		this->setVelocity(glm::vec3(5.75f, 0.f, 1.f)); // Initial velocity
	}

	void Planet::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
