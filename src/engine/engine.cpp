#include <engine/engine.hpp>
#include <core/input_manager.hpp>
#include <core/window.hpp>
#include <simulation/planet.hpp>
#include <simulation/simulation.hpp>
#include <graphics/material.hpp>
#include <graphics/mesh.hpp>
#include <graphics/shader.hpp>
#include <graphics/renderer.hpp>
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
		window = new Window(width, height, title.c_str());
		simulation = new Simulation();
		renderer = new Renderer(simulation->getEntities(), simulation->getCamera());
		inputManager = new InputManager(window, simulation->getCamera());

		// TODO: Put this logic into the material class and create a mesh/model factory for common shapes
		tmpShader = new Shader("assets/shaders/shader.vs", "assets/shaders/shader.fs");
		tmpLightShader = new Shader("assets/shaders/shader.vs", "assets/shaders/light_source.fs");
		tmpMat = new Material();
		tmpMat->shader = tmpShader;
		tmpLightMat = new Material();
		tmpLightMat->shader = tmpLightShader;

		tmpMesh = new Mesh(vertices, indices);

		simulation->spawnEntity(new Planet(tmpMesh, tmpMat, glm::vec3(0.f,0.f,0.f)));
		simulation->spawnEntity(new Planet(tmpMesh, tmpLightMat, glm::vec3(3.f,3.f,-5.f)));
	}

	Engine::~Engine() { 
		delete window;
		delete simulation;
		delete renderer;
		delete inputManager;
		delete tmpShader;
		delete tmpLightShader;
		delete tmpMat;
		delete tmpLightMat;
		delete tmpMesh;
		if (glfwInit()) glfwTerminate();
	}

	void Engine::run()
	{
		float deltaTime = 0.f, lastFrame = 0.f;
		while (!window->shouldClose())
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			inputManager->processInput(deltaTime);
			simulation->update(deltaTime);
			renderer->render();
			window->swapBuffers();
			window->pollEvents();
		}
	}
}
