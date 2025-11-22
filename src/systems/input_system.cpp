#include <systems/input_system.hpp>
#include <engine/window.hpp>
#include <engine/engine.hpp>

namespace solarsim {
	InputSystem::InputSystem(GLFWwindow* window) {
		if (window) {
			glfwSetCursorPosCallback(window, mouseCallback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	InputSystem::~InputSystem() {}

	void InputSystem::processInput(float deltaTime) {
		// Get scene from scene manager
		//
		// Get registry from scene
		//
		// Get entity with a transform component and active input component
		//
		// Handle input on the entity, not the camera
	}

	void InputSystem::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
		// Do the same as in processInput and rotate the entity
	}
}
