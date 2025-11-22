#pragma once

#include "shader.hpp"
#include <glm/vec3.hpp>

namespace solarsim {
	struct Material {
		Shader* shader;
		glm::vec3 albedo = {1.0f, 1.0f, 1.0f};
		float metallic = 0.0f;
		float roughness = 1.0f;
	};
}
