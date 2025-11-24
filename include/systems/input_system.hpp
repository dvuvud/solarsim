#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {
	class InputSystem {
		public:
			InputSystem(GLFWwindow* window);
			~InputSystem();
			void processInput(float deltaTime);
		private:
			void toggleMouseCapture();
			bool mouseCaptured = true;
			bool justCaptured = true;
			GLFWwindow* m_window;

			static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
