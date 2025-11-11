#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {
	class Window {
		public:
			Window(const unsigned int p_width, const unsigned int p_height, const char* p_title);
			~Window() { if (m_window) glfwDestroyWindow(m_window);}
			bool shouldClose() { return glfwWindowShouldClose(m_window); }
			void swapBuffers() { glfwSwapBuffers(m_window); }
			void pollEvents() { glfwPollEvents(); }
			GLFWwindow* getNativeWindow() { return m_window; }
		private:
			GLFWwindow* m_window;

			void static framebuffer_size_callback(GLFWwindow* p_window, int p_width, int p_height) { glViewport(0, 0, p_width, p_height); }
	};
}
