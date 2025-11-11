#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {

	class Window;
	class Camera;

	class InputManager {
		public:
			InputManager(Window* p_window, Camera* p_camera);
			void processInput(float deltaTime);
			void setCamera(Camera* p_camera) { m_camera = p_camera; }
		private:
			Window* m_window;
			Camera* m_camera;

			bool m_shouldCaptureMouse = true;
			bool m_firstMouse = true;
			float m_lastX = 0.0f;
			float m_lastY = 0.0f;

			void handleMouseMovement(float p_xpos, float p_ypos);
			void handleMouseScroll(double p_xoffset, double p_yoffset);

			static void mouseCallback(GLFWwindow* p_window, double p_xpos, double p_ypos);
			static void scrollCallback(GLFWwindow* p_window, double p_xoffset, double p_yoffset);
	};
}
