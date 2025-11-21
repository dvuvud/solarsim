#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/ext/quaternion_transform.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace solarsim {
	struct TransformComponent {
		glm::vec3 position{0.0f};
		glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
		glm::vec3 scale{1.0f};

		glm::vec3 forward() const { return rotation * glm::vec3(0, 0, -1); }
		glm::vec3 up() const { return rotation * glm::vec3(0, 1,  0); }
		glm::vec3 right() const { return rotation * glm::vec3(1, 0,  0); }

		mutable glm::mat4 modelMatrix;
		mutable bool dirty = true;
	};
}

