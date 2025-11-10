#pragma once

#include "../graphics/camera.hpp"
#include "window.hpp"

class InputManager {
	public:
		InputManager(Window* window, Camera* camera);
		void processInput(float deltaTime);
	private:
		Window* window = nullptr;
		Camera* camera = nullptr;

		bool shouldCaptureMouse = true;
		bool firstMouse = true;
		float lastX = 0.0f;
		float lastY = 0.0f;

		void handleMouseMovement(float xpos, float ypos);
		void handleMouseScroll(double xoffset, double yoffset);

		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
