#pragma once

#include <glm/vec3.hpp>
#include <string>

namespace solarsim {

	/**
	 * @brief Defines surface appearance properties for rendering
	 * 
	 * @warning Ensure shaderID references a valid compiled shader
	 */
	struct Material {
		/** Identifier for the shader program to use */
		std::string shaderID;
		/** Base color (RGB) */
		glm::vec3 albedo = glm::vec3(1.0f, 1.0f, 1.0f);
		/** Metallic factor (0 = dielectric, 1 = metal) */
		float metallic = 0.0f;
		/** Surface roughness (0 = smooth, 1 = rought) */
		float roughness = 1.0f;
	};
}
