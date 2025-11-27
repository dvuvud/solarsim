#pragma once

#include "registry.hpp"
#include <engine/renderer.hpp>
#include <systems/physics_system.hpp>

namespace solarsim {

	/**
	 * @brief Container for entities, components, and simulation state
	 * 
	 * @note Manages the complete game world state and simulation timing
	 * @warning Scene should be loaded/unloaded via SceneManager
	 */
	struct Scene {
		/** Registry managing all entities and components */
		Registry registry;
		/** Simulation speed multiplier */
		float timeScale = 1.0f;

		/** Whether simulation is paused */
		bool paused = false;
		/** Whether simulation runs in reverse */
		bool reverse = false;

		/**
		 * @brief Toggle simulation pause state
		 * @note When paused, systems don't process entity updates
		 */
		void togglePause() { paused = !paused; }
		/**
		 * @brief Toggle simulation direction (forward/reverse)
		 * @note Reverse mode may affect physics and animation systems
		 */
		void toggleReverse() { reverse = !reverse; }
	};
}
