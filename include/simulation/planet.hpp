#pragma once

#include <simulation/entity.hpp>

namespace solarsim {
	class Planet : public Entity {
		public:
			Planet(const Transform& transform, float m = 0.f, float r=1.f, const glm::vec3& iv = glm::vec3(0.0f));
			Planet(const Transform& transform,
					std::unique_ptr<Mesh>& p_mesh,
					std::unique_ptr<Material>& p_mat,
					float m = 0.0f,
					float r = 1.0f,
					const glm::vec3& iv = glm::vec3(0.0f));
			virtual ~Planet() = default;
			void update(float deltaTime) override;
	};
}
