#pragma once

namespace solarsim {

	/**
	 * @brief Handles physics simulation including gravity and N-body dynamics
	 * 
	 * @warning High timeScale values may cause simulation instability
	 */
	class PhysicsSystem {
		public:
			/**
			 * @brief Update physics simulation for one frame
			 * @param deltaTime Time step for physics integration in seconds
			 * 
			 * @note Applies gravitational forces and updates rigid body positions
			 * @doublenote ;)) Small deltaTime values provide more stable simulation
			 */
			void update(float deltaTime);
		private:
			/** Physics simulation speed multiplier */
			float timeScale = 1.0f;
			/** Gravitational constant */
			const float G = 10.0f;
			/** Softening factor to prevent numerical instability */
			const float SOFTENING_SQUARED = 1.0f;
	};
}
