#include <engine/engine.hpp>
#include <mesh/cube.hpp>
#include <iostream>

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
		// TODO: Put this logic into the material class and create a mesh/model factory for common shapes

		m_tmpShader = std::make_unique<Shader>("assets/shaders/shader.vs", "assets/shaders/shader.fs");
		m_tmpMat = std::make_unique<Material>(m_tmpShader.get());
		m_tmpLightShader = std::make_unique<Shader>("assets/shaders/shader.vs", "assets/shaders/light_source.fs");
		m_tmpLightMat = std::make_unique<Material>(m_tmpLightShader.get());

		m_tmpMesh = std::make_unique<Cube>();

		m_simulation->spawnEntity(std::make_unique<Planet>(m_tmpMesh.get(), m_tmpMat.get(), glm::vec3(-3.f,0.f,0.f)));
		m_simulation->spawnEntity(std::make_unique<Planet>(m_tmpMesh.get(), m_tmpLightMat.get(), glm::vec3(3.f,1.5f,-12.f)));
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
			m_renderer->render(m_simulation->getEntities(), m_simulation->getCamera());
			m_window->swapBuffers();
			m_window->pollEvents();
		}
	}
}
