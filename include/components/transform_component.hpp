#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/ext/quaternion_transform.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace solarsim {
	/**
	 * @brief Defines spatial properties and provides model matrix calculation
	 */
	struct TransformComponent {
		/** World space position vector */
		glm::vec3 position{0.0f};

		/** Orientation as a quaternion */
		glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};

		/** Scaling factors */
		glm::vec3 scale{1.0f};

		/** Cached tranformation matrix (set via getModelMatrix below) */
		mutable glm::mat4 modelMatrix;

		/** Flag indication if matrix needs recalculation */
		mutable bool dirty = true;

		/**
		 * @brief Computes the model transformation matrix
		 * 
		 * @return glm::mat4 The composed model matrix (translation * rotation * scale)
		 * 
		 * @note Only recalculates when dirty flag is set
		 * @warning Modifying position, rotation, or scale does NOT currently set dirty=true automatically
		 */
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

