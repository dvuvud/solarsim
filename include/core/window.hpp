#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {
	class Window {
		public:
			Window(const unsigned int p_width = 800, const unsigned int p_height = 600, const char* p_title = "solarsim");
			~Window() { if (m_window) glfwDestroyWindow(m_window);}
			bool shouldClose() { return glfwWindowShouldClose(m_window); }
			void swapBuffers() { glfwSwapBuffers(m_window); }
			void pollEvents() { glfwPollEvents(); }
			GLFWwindow* getNativeWindow() const { return m_window; }
		private:
			GLFWwindow* m_window;
			static void framebuffer_size_callback(GLFWwindow* w, int p_width, int p_height);
	};
}
