#include <engine/engine.hpp>
#include <mesh/cube.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>
#include <stdexcept>

namespace solarsim {

	Engine::Engine(unsigned int width, unsigned int height, const std::string& title)
	{
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize glfw");
		}
		m_window = std::make_unique<Window>(width, height, title.c_str());
		m_simulation = std::make_unique<Simulation>();
		m_renderer = std::make_unique<Renderer>();
		m_inputManager = std::make_unique<InputManager>(m_window.get(), m_simulation.get());

		Transform sunTransform;
		sunTransform.position = glm::vec3(0.f, 1.f, 0.f);
		sunTransform.scale = glm::vec3(5.f);
		Transform earthTransform;
		earthTransform.position = glm::vec3(0.f, 1.f, -50.f);
		earthTransform.scale = glm::vec3(2.f);
		m_simulation->spawnEntity(std::make_unique<Planet>(earthTransform, 200.f, 1.f));
		m_simulation->spawnEntity(std::make_unique<Sun>(sunTransform, 5000.f, 1.f));
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
