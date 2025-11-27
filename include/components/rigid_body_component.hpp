#pragma once

#include "glm/vec3.hpp"

namespace solarsim {
	/**
	 * @brief Provides physics properties for dynamic entity simulation
	 */
	struct RigidBodyComponent {
		/** Mass of the entity in arbitrary units */
		float mass = 1.0f;

		/** Current velocity vector */
		glm::vec3 vel = glm::vec3(0.0f);

		/** Whether gravity affects this entity (Currently not implemented) */
		bool useGravity = true;
	};
}

