#pragma once

#include <simulation/entity.hpp>

namespace solarsim {
	class Planet : public Entity {
		public:
			Planet(Mesh* mesh = nullptr, Material* material = nullptr, const glm::vec3& position = glm::vec3(0.0f));
			virtual ~Planet() = default;
			void update(float deltaTime) override;
			virtual void render(Shader& shader) override;
		private:
			// TODO: Implement the following in planet construction
			float m_mass;
			float m_radius;
	};
}
