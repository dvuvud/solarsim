#include <simulation/sun.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <iostream>

namespace solarsim {
	Sun::Sun(const Transform& transform, float m, float r, float lr)
		: m_material("assets/shaders/sun.vert", "assets/shaders/sun.frag"),
		Entity(transform, m_mesh, m_material, m, r), m_lightRadius(lr)
		{

		}

	void Sun::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
