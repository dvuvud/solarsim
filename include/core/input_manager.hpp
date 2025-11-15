#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {

	class Window;
	class Simulation;

	class InputManager {
		public:
			InputManager(Window* p_window, Simulation* p_sim);
			void processInput(float& deltaTime);
			void setSimulation(Simulation* p_sim) { m_sim = p_sim; }
		private:
			Window* m_window;
			Simulation* m_sim;

			bool m_shouldCaptureMouse = true;
			bool m_firstMouse = true;
			float m_lastX = 0.0f;
			float m_lastY = 0.0f;

			void handleMouseMovement(float p_xpos, float p_ypos);
			void handleMouseScroll(double p_xoffset, double p_yoffset);
			void toggleMouseCapture(GLFWwindow* w);

			static void mouseCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);
			static void scrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);
	};
}
