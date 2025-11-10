#pragma once

#include <core/window.hpp>
#include <core/input_manager.hpp>
#include <graphics/renderer.hpp>
#include <simulation/simulation.hpp>

class Engine {
	public:
		Engine() = default;
		~Engine() { if (glfwInit()) glfwTerminate(); }
		void init(unsigned int width = 800, unsigned int height = 600, const std::string& = "solarsim");
		void run();
	private:
		std::unique_ptr<Window> window;
		std::unique_ptr<Simulation> simulation;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<InputManager> inputManager;

		// Temporary for testing, move to respective factories or similar
		std::unique_ptr<Mesh> tmpMesh;
		std::unique_ptr<Material> tmpMat;
		std::unique_ptr<Shader> tmpShader;
};
