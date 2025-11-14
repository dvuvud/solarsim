#include <engine/engine.hpp>
#include <mesh/cube.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>

namespace solarsim {

	Engine::Engine(unsigned int width, unsigned int height, const std::string& title)
	{
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize glfw");
		}
		m_window = std::make_unique<Window>(width, height, title.c_str());
		m_simulation = std::make_unique<Simulation>();
		m_renderer = std::make_unique<Renderer>();
		m_inputManager = std::make_unique<InputManager>(m_window.get(), m_simulation->getCamera());

		m_simulation->spawnEntity(std::make_unique<Planet>(glm::vec3(-5.f,0.f,0.f)));
		m_simulation->spawnSun(std::make_unique<Sun>(glm::vec3(0.f,0.f,0.f)));
	}

	Engine::~Engine() { 
		if (glfwInit()) glfwTerminate();
	}

	void Engine::run()
	{
		float deltaTime = 0.f, lastFrame = 0.f;
		while (!m_window->shouldClose())
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_inputManager->processInput(deltaTime);
			m_simulation->update(deltaTime);
			m_renderer->render(m_simulation);
			m_window->swapBuffers();
			m_window->pollEvents();
		}
	}
}
