#include <simulation/planet.hpp>
#include <mesh/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Planet::Planet(Mesh* mesh, Material* material, const glm::vec3& position)
		: Entity(Transform{.position=position}, mesh, material)
		{

		}

	void Planet::update(float deltaTime)
	{
		// TODO: Implement planet specific update logic
	}
}
