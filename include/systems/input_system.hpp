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
			GLFWwindow* m_window;
	};
}
