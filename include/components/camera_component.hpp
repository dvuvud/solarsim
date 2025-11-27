#pragma once

#include <glm/glm.hpp>

namespace solarsim {
	/**
	 * @brief Defines camera properties for rendering and view projection
	 * 
	 * @note Only one camera should have primary=true at any time
	 * @warning Inconsistent aspect ratios may cause visual distortion
	 */
	struct CameraComponent {
		/** Field of view in degrees. Default: 45.0f */
		float fov = 45.0f;

		/** Near clipping plane distance. Default: 0.1f */
		float near = 0.1f;

		/** Far clipping plane distance. Default: 2000.0f */
		float far = 2000.f;

		/** Aspect ratio (width/height). Default: 800.0f/600.0f */
		float aspect = 800.0f / 600.0f;

		/** Whether this is the primary camera. Only one should be true. */
		bool primary = true;
	};
}
