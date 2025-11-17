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
		sunTransform.position = glm::vec3(0.0f, 1.0f, 0.0f);
		sunTransform.scale = glm::vec3(10.0f);
		Transform sun2Transform;
		sun2Transform.position = glm::vec3(-100.0f, 1.0f, 0.0f);
		sun2Transform.scale = glm::vec3(20.f);
		Transform earthTransform;
		earthTransform.position = glm::vec3(0.f, 1.f, -100.f);
		earthTransform.scale = glm::vec3(5.f);
		std::unique_ptr<Material> earthMat = std::make_unique<Material>("assets/shaders/planet.vert", "assets/shaders/planet.frag");
		std::unique_ptr<Material> sunMat = std::make_unique<Material>("assets/shaders/sun.vert", "assets/shaders/sun.frag");
		std::unique_ptr<Material> sun2Mat = std::make_unique<Material>("assets/shaders/sun.vert", "assets/shaders/sun.frag");
		std::unique_ptr<Mesh> earthMesh = std::make_unique<Cube>();
		std::unique_ptr<Mesh> sunMesh = std::make_unique<Cube>();
		std::unique_ptr<Mesh> sun2Mesh = std::make_unique<Cube>();

		m_simulation->spawnEntity(std::make_unique<Planet>(earthTransform, earthMesh, earthMat, 200.0f, 1.0f, glm::vec3(3.75f, 0.0f, 0.0f)));
		m_simulation->spawnEntity(std::make_unique<Sun>(sunTransform, sunMesh, sunMat, 1000.0f, 1.0f, 100.0f, glm::vec3(0.5f, 1.0f, 1.0f)));
		m_simulation->spawnEntity(std::make_unique<Sun>(sun2Transform, sun2Mesh, sun2Mat, 1000.0f, 1.0f, 200.0f, glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(1.0f, 0.0f, 6.0f)));
	}

	Engine::~Engine() { 
		if (glfwInit()) glfwTerminate();
	}

	void Engine::run()
	{
		float deltaTime = 0.f, lastFrame = 0.f;
		while (!m_window->shouldClose())
		{
			float currentFrame = (float)glfwGetTime();
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
