#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "component.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace solarsim {
	class TransformComponent : public Component {
		public:
			glm::vec3 m_position{0.0f};
			glm::quat m_rotation{1.0f, 0.0f, 0.0f, 0.0f};
			glm::vec3 m_scale{1.0f};

			void setPosition(const glm::vec3& pos) { m_position = pos; m_dirty = true; }
			void setRotation(const glm::quat& rot) { m_rotation = rot; m_dirty = true; }
			void setScale(const glm::vec3& scale) { m_scale = scale; m_dirty = true; }

			[[nodiscard]] glm::mat4 getModelMatrix() const noexcept {
				if (m_dirty) {
					m_cachedMatrix = glm::translate(glm::mat4(1.0f), m_position) *
						glm::toMat4(m_rotation) *
						glm::scale(glm::mat4(1.0f), m_scale);
					m_dirty = false;
				}
				return m_cachedMatrix;
			}
		private:
			mutable glm::mat4 m_cachedMatrix{1.0f};
			mutable bool m_dirty{true};
	};
}

