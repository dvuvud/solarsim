#pragma once

#include "registry.hpp"
#include <systems/physics_system.hpp>

namespace solarsim {
	struct Scene {
		Registry registry;

		float timeScale = 1.0f;
		bool paused = false;
		bool reverse = false;

		PhysicsSystem physicsSystem;
		RenderSystem renderSystem;
		InputManager inputManager;
	};
}
