#include <systems/input_system.hpp>
#include <engine/window.hpp>
#include <engine/engine.hpp>

namespace solarsim {
	InputSystem::InputSystem() {
		Window* window = Engine::get().window();
		if (window) {
			GLFWwindow* w = window->getNativeWindow();

			glfwSetCursorPosCallback(w, mouseCallback);
			glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
