#include <simulation/simulation.hpp>
#include <core/window.hpp>
#include <core/input_manager.hpp>

namespace solarsim {
	InputManager::InputManager(Window* p_window, Simulation* p_sim) {
		m_window = p_window;
		m_sim = p_sim;

		GLFWwindow* w = p_window->getNativeWindow();
		glfwSetWindowUserPointer(w, this);

		glfwSetCursorPosCallback(w, mouseCallback);
		glfwSetScrollCallback(w, scrollCallback);
		glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void InputManager::processInput(float& deltaTime) {
		Camera* cam = m_sim ? m_sim->getCamera() : nullptr;
		if (!m_window || !cam) return;
		GLFWwindow* w = m_window->getNativeWindow();
		if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
			cam->ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
			cam->ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
			cam->ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
			cam->ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS)
			cam->ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cam->ProcessKeyboard(DOWN, deltaTime);

		if (glfwGetKey(w, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(w, true);
		static bool rPressedLastFrame = false;
		if (glfwGetKey(w, GLFW_KEY_R) == GLFW_PRESS) {
			if (!rPressedLastFrame) {
				rPressedLastFrame = true;
				m_sim->toggleReverse();
			}
		} else {
			rPressedLastFrame = false;
		}
		static bool tabPressedLastFrame = false;
		if (glfwGetKey(w, GLFW_KEY_TAB) == GLFW_PRESS) {
			if (!tabPressedLastFrame) {
				tabPressedLastFrame = true;
				toggleMouseCapture(w);
			}
		} else {
			tabPressedLastFrame = false;
		}
		static bool pPressedLastFrame = false;
		if (glfwGetKey(w, GLFW_KEY_P) == GLFW_PRESS) {
			if (!pPressedLastFrame) {
				pPressedLastFrame = true;
				m_sim->togglePause();
			}
		} else {
			pPressedLastFrame = false;
		}
	}

	void InputManager::toggleMouseCapture(GLFWwindow* w) {
		if (m_shouldCaptureMouse) {
			glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_shouldCaptureMouse = false;
		} else {
			glfwSetInputMode(w, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_firstMouse = true;
			m_shouldCaptureMouse = true;
		}
	}

	void InputManager::mouseCallback(GLFWwindow* p_window, double p_xpos, double p_ypos) {
		InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(p_window));
		if (manager) {
			manager->handleMouseMovement(static_cast<float>(p_xpos), static_cast<float>(p_ypos));
		}
	}

	void InputManager::handleMouseMovement(float p_xpos, float p_ypos) {
		if (!m_shouldCaptureMouse) return;
		if (m_firstMouse)
		{
			m_lastX = p_xpos;
			m_lastY = p_ypos;
			m_firstMouse = false;
		}

		float xoffset = p_xpos - m_lastX;
		float yoffset = m_lastY - p_ypos;

		m_lastX = p_xpos;
		m_lastY = p_ypos;

		Camera* cam = m_sim ? m_sim->getCamera() : nullptr;
		if (cam) {
			cam->ProcessMouseMovement(xoffset, yoffset);
		}
	}

	void InputManager::scrollCallback(GLFWwindow* window, double p_xoffset, double p_yoffset) {
		InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
		if (manager) {
			manager->handleMouseScroll(p_xoffset, p_yoffset);
		}
	}

	void InputManager::handleMouseScroll(double p_xoffset, double p_yoffset) {
		Camera* cam = m_sim ? m_sim->getCamera() : nullptr;
		if (cam) {
			cam->ProcessMouseScroll(static_cast<float>(p_yoffset)); 
		}
	}
}
