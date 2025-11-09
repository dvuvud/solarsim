#pragma once

#include <GLFW/glfw3.h>

class Window {
	public:
		bool init(const unsigned int width, const unsigned int height, const char* title);
		bool shouldClose();
		void swapBuffers();
		void pollEvents();
		void cleanup();
		GLFWwindow* getNativeWindow();
		~Window() { if (window) glfwDestroyWindow(window);}
	private:
		GLFWwindow* window = nullptr;

		void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

