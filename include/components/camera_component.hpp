#pragma once

#include <glm/glm.hpp>

namespace solarsim {
	struct CameraComponent {
		float fov = 45.0f;
		float near = 0.1f;
		float far = 2000.f;
		float aspect = 800.0f / 600.0f;

		bool primary = true;
	};
}
