#pragma once

#include <mesh/cube.hpp>
#include <graphics/material.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	class Sun : public Entity {
		public:
			Sun(const Transform& transform = Transform{.position = glm::vec3(0.f)}, float m = 0.f, float r=1.f, float lr=100.f);
			virtual ~Sun() = default;
			void update(float deltaTime) override;
			float getLightRadius() const { return m_lightRadius; }
		private:
			Material m_material;
			Cube m_mesh;
			float m_mass;
			float m_radius;
			float m_lightRadius;
	};
}
