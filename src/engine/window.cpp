#include <glad/glad.h>
#include <core/window.hpp>
#include <simulation/simulation.hpp>

#include <iostream>

namespace solarsim {
	Window::Window(const unsigned int p_width, const unsigned int p_height, const char* p_title, Simulation* p_sim) : m_sim(p_sim)
	{
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
	}
	void Window::framebuffer_size_callback(GLFWwindow* w, int p_width, int p_height) {
		Simulation* sim = static_cast<Window*>(glfwGetWindowUserPointer(w))->m_sim;
		if (sim) sim->setCameraAspectRatio((float)p_width / p_height);
		glViewport(0, 0, p_width, p_height);
	}
}
