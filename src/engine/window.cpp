#include <glad/glad.h>
#include <engine/window.hpp>
#include <managers/scene_manager.hpp>
#include <engine/engine.hpp>
#include <components/camera_component.hpp>
#include <scene/scene.hpp>
#include <stdexcept>

#include <iostream>

namespace solarsim {
	Window::Window(const uint32_t p_width, const uint32_t p_height, const char* p_title) {
		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		m_window = glfwCreateWindow(p_width, p_height, p_title, NULL, NULL);
		if (m_window == NULL)
		{
			throw std::runtime_error("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::runtime_error("Failed to initialize GLAD");
		}
		glEnable(GL_DEPTH_TEST);
	}
	Window::~Window() {
		if (m_window) glfwDestroyWindow(m_window);
		if (glfwInit()) glfwTerminate();
	}
	void Window::framebuffer_size_callback(GLFWwindow* w, int p_width, int p_height) {
		glViewport(0, 0, p_width, p_height);

		auto scene = SceneManager::get().active();
		if (!scene) return;
		auto& reg = scene->registry;
		auto camOpt = Engine::getPrimaryCamera(reg);
		if (camOpt == -1) return;
		Entity camEntity = *camOpt;
		auto& camComp = reg.getComponent<CameraComponent>(camEntity);
		camComp.aspect = (float)p_width / p_height;
	}
}
