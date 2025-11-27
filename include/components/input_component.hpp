#pragma once

namespace solarsim {
	/**
	 * @brief Handles user input processing for entity control
	 */
	struct InputComponent {
		/** Whether this entity should process input */
		bool takeInput = true;

		/** Movement speed in units per second */
		float movementSpeed = 100.0f;

		/** Mouse look sensitivity multiplier */
		float mouseSensitivity = 0.1f;
	};
}
