#pragma once

#include "glm/vec3.hpp"

namespace solarsim {
	struct Rigidbodycomponent {
		float mass = 1.0f;
		glm::vec3 vel = glm::vec3(0.0f);
		bool useGravity = true;
	};
}

