#include <systems/input_system.hpp>

#include <scene/scene.hpp>
#include <managers/scene_manager.hpp>

#include <engine/window.hpp>
#include <engine/engine.hpp>

#include <components/input_component.hpp>
#include <components/transform_component.hpp>

namespace solarsim {
	InputSystem::InputSystem(GLFWwindow* window) : m_window(window) {
		if (window) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	InputSystem::~InputSystem() {}

	void InputSystem::processInput(float deltaTime) {
		Scene* scene = SceneManager::get().active();
		if (!scene) return;
		Registry& registry = scene->registry;

		static bool rLast = false;
		static bool tabLast = false;
		static bool pLast = false;

		for (Entity e : registry.view<InputComponent, TransformComponent>()) {
			auto& transform = registry.getComponent<TransformComponent>(e);
			auto& input = registry.getComponent<InputComponent>(e);

			glm::vec3 forward = transform.rotation * glm::vec3(0,0,-1);
			glm::vec3 right = transform.rotation * glm::vec3(1,0,0);
			glm::vec3 up = glm::vec3(0,1,0);

			float speed = input.movementSpeed * deltaTime;

			if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
				transform.position += forward * speed;
			if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
				transform.position -= forward * speed;

			if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
				transform.position += right * speed;
			if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
				transform.position -= right * speed;

			if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
				transform.position += up * speed;
			if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
				transform.position -= up * speed;

			double mouseX, mouseY;
			glfwGetCursorPos(m_window, &mouseX, &mouseY);

			static double lastX = mouseX, lastY = mouseY;
			float dx = float(mouseX - lastX);
			float dy = float(lastY - mouseY);

			lastX = mouseX;
			lastY = mouseY;

			float sens = input.mouseSensitivity;

			glm::quat yaw = glm::angleAxis(dx * sens, glm::vec3(0,1,0));
			glm::quat pitch = glm::angleAxis(dy * sens, glm::vec3(1,0,0));
			transform.rotation = yaw * transform.rotation * pitch;
		}

		// ------ GLOBAL KEYS -------

		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);

		if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS) {
			if (!rLast) {
				rLast = true;
				Scene* scene = SceneManager::get().active();
				if (scene)
					scene->toggleReverse();
			}
		} else rLast = false;

		if (glfwGetKey(m_window, GLFW_KEY_TAB) == GLFW_PRESS) {
			if (!tabLast) {
				tabLast = true;
				toggleMouseCapture();
			}
		} else tabLast = false;

		if (glfwGetKey(m_window, GLFW_KEY_P) == GLFW_PRESS) {
			if (!pLast) {
				pLast = true;
				Scene* scene = SceneManager::get().active();
				if (scene)
					scene->togglePause();
			}
		} else pLast = false;
	}

	void InputSystem::toggleMouseCapture() {
		mouseCaptured = !mouseCaptured;

		if (mouseCaptured)
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			// Clear initial mouse delta spike
			double x, y;
			glfwGetCursorPos(m_window, &x, &y);
		}
		else
		{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

}
