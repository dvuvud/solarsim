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
			glm::mat4 getModelMatrix() const {
				glm::mat4 T = glm::translate(glm::mat4(1.0f), m_position);
				glm::mat4 R = glm::toMat4(m_rotation);
				glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);
				return T * R * S;
			}
	};
}

