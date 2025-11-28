#pragma once

#include <string>
#include <glm/vec3.hpp>

namespace solarsim {
	/**
	 * @brief Defines light source properties for scene illumination
	 * 
	 * @note Currently only a point light implementation
	 */
	struct LightComponent {
		/** Identifier for the mesh geometry resource */
		std::string meshID;

		/** Identifier for the shader program to use */
		std::string shaderID;

		/** RGB color of the light */
		glm::vec3 color = glm::vec3(1.0f);

		/** Effective radius/range of the light */
		float radius = 1000.0f;
	};
}
