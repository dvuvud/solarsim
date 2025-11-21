#pragma once

#include "glm/vec3.hpp"

namespace solarsim {
	struct Rigidbodycomponent {
		float mass;
		glm::vec3 vel;
		bool useGravity;
	};
}

