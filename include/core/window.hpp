#pragma once

#include <GLFW/glfw3.h>

class Window {
	public:
		Window(const unsigned int width, const unsigned int height, const char* title);
		~Window() { if (window) glfwDestroyWindow(window);}
		bool shouldClose();
		void swapBuffers();
		void pollEvents();
		GLFWwindow* getNativeWindow();
	private:
		GLFWwindow* window = nullptr;

		void static framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

