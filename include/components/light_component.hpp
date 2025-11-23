#pragma once

#include <glm/vec3.hpp>

namespace solarsim {
	struct LightComponent {
		glm::vec3 color = glm::vec3(1.0f);
		float radius = 135.0f;
	};
}
