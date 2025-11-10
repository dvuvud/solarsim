#include "input_manager.hpp"

InputManager::InputManager(Window* window, Camera* camera) {
	this->window = window;
	this->camera = camera;

	GLFWwindow* w = window->getNativeWindow();
	glfwSetWindowUserPointer(w, this);

	glfwSetCursorPosCallback(w, mouseCallback);
	glfwSetScrollCallback(w, scrollCallback);
	glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputManager::processInput(float deltaTime) {
	if (!window || !window->getNativeWindow()) return;
	GLFWwindow* w = window->getNativeWindow();
	if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(w, true);
	if (glfwGetKey(w, GLFW_KEY_TAB) == GLFW_PRESS) {
		if (shouldCaptureMouse) {
			glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			shouldCaptureMouse = false;
		}
	} else {
		if (!shouldCaptureMouse) {
			glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
			shouldCaptureMouse = true;
		}
	}
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) {
		manager->handleMouseMovement(static_cast<float>(xpos), static_cast<float>(ypos));
	}
}

void InputManager::handleMouseMovement(float xpos, float ypos) {
	if (!shouldCaptureMouse) return;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (camera) {
		camera->ProcessMouseMovement(xoffset, yoffset);
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) {
		manager->handleMouseScroll(xoffset, yoffset);
	}
}

void InputManager::handleMouseScroll(double xoffset, double yoffset) {
	if (camera) {
		camera->ProcessMouseScroll(static_cast<float>(yoffset)); 
	}
}
