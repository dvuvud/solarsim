#include <simulation/sun.hpp>
#include <mesh/cube.hpp>
#include <graphics/shader.hpp>
#include <graphics/camera.hpp>
#include <memory>
#include <iostream>

namespace solarsim {
	Sun::Sun(const Transform& transform, float m, float r, float lr)
		: Entity(transform,
				std::make_unique<Cube>(),
				std::make_unique<Material>("assets/shaders/sun.vert", "assets/shaders/sun.frag"),
				m,
				r),
		m_lightRadius(lr)
	{

	}

	void Sun::update(float deltaTime)
	{
		Entity::update(deltaTime);
	}
}
