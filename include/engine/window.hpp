#pragma once

#include <GLFW/glfw3.h>

namespace solarsim {

	/**
	 * @brief Manages window creation, events, and GLFW context
	 * 
	 * @note Wraps GLFW window functionality
	 * @warning GLFW must be initialized before creating Window instances
	 */
	class Window {
		public:
			/**
			 * @brief Create a new window
			 * @param p_width Window width in pixels
			 * @param p_height Window height in pixels
			 * @param p_title Window title
			 * 
			 * @throws std::runtime_error if window creation fails
			 */
			Window(const uint32_t p_width = 800, const uint32_t p_height = 600, const char* p_title = "solarsim");
			~Window();

			/**
			 * @brief Check if window should close
			 * @return bool True if window close requested
			 */
			bool shouldClose() { return glfwWindowShouldClose(m_window); }

			/**
			 * @brief Swap front and back buffers
			 * @note Call this once per frame after rendering
			 */
			void swapBuffers() { glfwSwapBuffers(m_window); }

			/**
			 * @brief Process pending window events
			 * @note Call this once per frame before rendering
			 */
			void pollEvents() { glfwPollEvents(); }

			/**
			 * @brief Get native GLFW window handle
			 * @return GLFWwindow* Raw GLFW window pointer
			 */
			GLFWwindow* getNativeWindow() const { return m_window; }
		private:
			/** Native GLFW window handle */
			GLFWwindow* m_window;

			/**
			 * @brief GLFW framebuffer resize callback
			 * @param w GLFW window that was resized
			 * @param p_width New framebuffer width
			 * @param p_height New framebuffer height
			 * 
			 * @note Updates the aspect ratio of the primary camera if present
			 */
			static void framebuffer_size_callback(GLFWwindow* w, int p_width, int p_height);
	};
}
