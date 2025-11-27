#pragma once

#include <glm/vec3.hpp>

namespace solarsim {
	/**
	 * @brief Defines light source properties for scene illumination
	 * 
	 * @note Currently only a point light implementation
	 */
	struct LightComponent {
		/** RGB color of the light */
		glm::vec3 color = glm::vec3(1.0f);

		/** Effective radius/range of the light */
		float radius = 135.0f;
	};
}
