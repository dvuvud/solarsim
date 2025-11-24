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

		mutable glm::mat4 modelMatrix;
		mutable bool dirty = true;

		glm::mat4 getModelMatrix() const {
			if (dirty) {
				modelMatrix = 
					glm::translate(glm::mat4(1.0f), position) * 
					glm::toMat4(rotation) * 
					glm::scale(glm::mat4(1.0f), scale);
				dirty = false;
			}
			return modelMatrix;
		}
	};
}

