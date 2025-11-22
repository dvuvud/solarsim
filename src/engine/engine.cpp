#include <engine/engine.hpp>
#include <engine/window.hpp>
#include <engine/renderer.hpp>
#include <systems/input_system.hpp>
#include <systems/physics_system.hpp>
#include <scene/scene.hpp>

namespace solarsim {
	Engine::Engine() {
		init();
	}

	Engine::~Engine() {}

	void Engine::init() {
		m_window = std::make_unique<Window>(800, 600, "solarsim");
		m_inputSystem = std::make_unique<InputSystem>(m_window->getNativeWindow());
		m_physicsSystem = std::make_unique<PhysicsSystem>();
		m_renderer = std::make_unique<Renderer>();
	}

	void Engine::run() {
		float deltaTime = 0.0f, lastFrame = (float)glfwGetTime();
		while (!m_window->shouldClose()) {
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_window->pollEvents();
			m_inputSystem->processInput(deltaTime);

			m_physicsSystem->update(deltaTime);

			m_renderer->render();

			m_window->swapBuffers();
		}
	}
}
