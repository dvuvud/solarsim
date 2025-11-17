#pragma once

#include <simulation/entity.hpp>

namespace solarsim {
	class Sun : public Entity {
		public:
			Sun(const Transform& transform, float m = 0.f, float r=1.f, float lr=100.f, const glm::vec3& lc = glm::vec3(1.0f), const glm::vec3& iv = glm::vec3(0.0f));
			Sun(const Transform& transform,
					std::unique_ptr<Mesh>& p_mesh,
					std::unique_ptr<Material>& p_mat,
					float m = 0.f,
					float r = 1.f,
					float lr = 100.f,
					const glm::vec3& lc = glm::vec3(1.0f),
					const glm::vec3& iv = glm::vec3(0.0f));
			virtual ~Sun() = default;
			void update(float deltaTime) override;
			float getLightRadius() const { return m_lightRadius; }
			const glm::vec3& getLightColor() const { return m_lightColor; }
		private:
			float m_lightRadius;
			glm::vec3 m_lightColor;
	};
}
