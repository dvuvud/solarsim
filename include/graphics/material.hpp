#pragma once

#include <glm/vec3.hpp>
#include <string>

namespace solarsim {
	struct Material {
		std::string shaderID;
		glm::vec3 albedo = {1.0f, 1.0f, 1.0f};
		float metallic = 0.0f;
		float roughness = 1.0f;
	};
}
