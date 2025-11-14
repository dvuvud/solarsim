#pragma once

#include <mesh/cube.hpp>
#include <graphics/material.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	class Planet : public Entity {
		public:
			Planet(const glm::vec3& position = glm::vec3(0.0f), float m = 0.f, float r=1.f);
			virtual ~Planet() = default;
			void update(float deltaTime) override;
		private:
			Material m_material;
			Cube m_mesh;
			float m_mass;
			float m_radius;
	};
}
