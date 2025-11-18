#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {
	class Simulation;
	class Window {
		public:
			Window(const unsigned int p_width, const unsigned int p_height, const char* p_title, Simulation* p_sim = nullptr);
			~Window() { if (m_window) glfwDestroyWindow(m_window);}
			bool shouldClose() { return glfwWindowShouldClose(m_window); }
			void swapBuffers() { glfwSwapBuffers(m_window); }
			void pollEvents() { glfwPollEvents(); }
			GLFWwindow* getNativeWindow() const { return m_window; }
		private:
			GLFWwindow* m_window;
			Simulation* m_sim;
			static void framebuffer_size_callback(GLFWwindow* w, int p_width, int p_height);
	};
}
