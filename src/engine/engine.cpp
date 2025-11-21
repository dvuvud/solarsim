#include <engine/engine.hpp>
#include <core/window.hpp>
#include <core/input_manager.hpp>
#include <graphics/renderer.hpp>
#include <managers/simulation_manager.hpp>
#include <mesh/cube.hpp>
#include <stdexcept>

namespace solarsim {

	Engine::Engine()
	{
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize glfw");
		}
		m_window = new Window();
		m_renderer = new Renderer();
		m_inputManager = new InputManager();
		current = this;
	}

	Engine::~Engine() { 
		if (glfwInit()) 
			glfwTerminate();
		if (m_window) 
			delete m_window;
		if (m_renderer)
			delete m_renderer;
		if (m_inputManager)
			delete m_inputManager;
	}

	void Engine::run()
	{
		float deltaTime = 0.f, lastFrame = (float)glfwGetTime();
		while (!m_window->shouldClose())
		{
			float currentFrame = (float)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (deltaTime > 0.1f)
				deltaTime = 0.1f;

			m_window->pollEvents();
			m_inputManager->processInput(deltaTime);

			Simulation& currentSim = SimulationManager::getActiveSimulation();
			currentSim.update(deltaTime);

			m_renderer->render(currentSim);

			m_window->swapBuffers();
		}
	}
}
