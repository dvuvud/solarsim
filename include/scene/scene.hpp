#pragma once

#include "registry.hpp"
#include <engine/renderer.hpp>
#include <systems/physics_system.hpp>

namespace solarsim {
	struct Scene {
		Registry registry;

		float timeScale = 1.0f;

		bool paused = false;
		bool reverse = false;
		void togglePause() { paused = !paused; }
		void toggleReverse() { reverse = !reverse; }
	};
}
