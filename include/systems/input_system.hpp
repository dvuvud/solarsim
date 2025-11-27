#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {

	/**
	 * @brief Handles user input processing and mouse/keyboard state management
	 */
	class InputSystem {
		public:
			/**
			 * @brief Construct the input system with a GLFW window
			 * @param window Pointer to the GLFW window to capture input from
			 */
			InputSystem(GLFWwindow* window);
			~InputSystem();

			/**
			 * @brief Process all input for the current frame
			 * @param deltaTime Time since last frame in seconds
			 */
			void processInput(float deltaTime);
		private:
			/**
			 * @brief Toggle mouse capture/release mode
			 */
			void toggleMouseCapture();
			/** Whether mouse is currently captured */
			bool mouseCaptured = true;
			/** Flag for handling initial capture state */
			bool justCaptured = true;
			/** GLFW window handle for input processing */
			GLFWwindow* m_window;

			/**
			 * @brief GLFW scroll callback for mouse wheel input
			 * @param window GLFW window that received the event
			 * @param xoffset Horizontal scroll offset
			 * @param yoffset Vertical scroll offset
			 * 
			 * @note Static method that forwards to instance methods
			 */
			static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
