#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <core/input_manager.hpp>
#include <core/window.hpp>
#include <simulation/simulation.hpp>
#include <graphics/material.hpp>
#include <graphics/shader.hpp>
#include <graphics/renderer.hpp>
#include <mesh/mesh.hpp>
#include <memory>

namespace solarsim {

	class Engine {
		public:
			static Engine* Current() { return current; }
			void SetCurrent() { current = this; }
			Engine(unsigned int width = 800, unsigned int height = 600, const std::string& title = "solarsim");
			~Engine();
			void run();
		private:
			static Engine* current;
			std::unique_ptr<Window> m_window;
			std::unique_ptr<Simulation> m_simulation;
			std::unique_ptr<Renderer> m_renderer;
			std::unique_ptr<InputManager> m_inputManager;
	};
}
