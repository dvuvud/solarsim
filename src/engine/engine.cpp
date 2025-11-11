#include <engine/engine.hpp>
#include <iostream>

namespace solarsim {
	// Put common shapes in factory later
	const std::vector<Vertex> vertices = {
		// 8 unique corner vertices
		{ {-0.5,-0.5,-0.5}, {0,0,0}, {0,0} }, // v0
		{ { 0.5,-0.5,-0.5}, {0,0,0}, {1,0} }, // v1
		{ { 0.5, 0.5,-0.5}, {0,0,0}, {1,1} }, // v2
		{ {-0.5, 0.5,-0.5}, {0,0,0}, {0,1} }, // v3
		{ {-0.5,-0.5, 0.5}, {0,0,0}, {0,0} }, // v4
		{ { 0.5,-0.5, 0.5}, {0,0,0}, {1,0} }, // v5
		{ { 0.5, 0.5, 0.5}, {0,0,0}, {1,1} }, // v6
		{ {-0.5, 0.5, 0.5}, {0,0,0}, {0,1} }, // v7
	};

	const std::vector<unsigned int> indices = {
		// Front face: uses v0, v1, v2, v3
		0, 1, 2,   // first triangle
		2, 3, 0,   // second triangle

		// Back face (uses vertices 4,5,6,7)  
		5, 4, 7,   // first triangle
		7, 6, 5,   // second triangle

		// Left face (uses vertices 4,0,3,7)
		4, 0, 3,   // first triangle
		3, 7, 4,   // second triangle

		// Right face (uses vertices 1,5,6,2)
		1, 5, 6,   // first triangle  
		6, 2, 1,   // second triangle

		// Bottom face (uses vertices 4,5,1,0)
		4, 5, 1,   // first triangle
		1, 0, 4,   // second triangle

		// Top face (uses vertices 3,2,6,7)
		3, 2, 6,   // first triangle
		6, 7, 3,   // second triangle
	};

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
		m_tmpMesh = std::make_unique<Mesh>(vertices, indices);

		m_simulation->spawnEntity(std::make_unique<Planet>(m_tmpMesh.get(), m_tmpMat.get(), glm::vec3(0.f,0.f,0.f)));
		m_simulation->spawnEntity(std::make_unique<Planet>(m_tmpMesh.get(), m_tmpLightMat.get(), glm::vec3(3.f,3.f,-5.f)));
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
