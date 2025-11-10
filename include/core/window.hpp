#pragma once

#include <GLFW/glfw3.h>

class Window {
	public:
		Window(const unsigned int width, const unsigned int height, const char* title);
		~Window() { if (window) glfwDestroyWindow(window);}
		bool shouldClose() { return glfwWindowShouldClose(window); }
		void swapBuffers() { glfwSwapBuffers(window); }
		void pollEvents() { glfwPollEvents(); }
		GLFWwindow* getNativeWindow() { return window; }
	private:
		GLFWwindow* window;

		void static framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
};
