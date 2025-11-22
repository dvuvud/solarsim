#include <engine/engine.hpp>
#include <engine/window.hpp>
#include <engine/renderer.hpp>

#include <systems/input_system.hpp>
#include <systems/physics_system.hpp>

#include <managers/scene_manager.hpp>
#include <scene/scene.hpp>

#include <components/transform_component.hpp>
#include <components/mesh_component.hpp>
#include <components/camera_component.hpp>

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
		SceneManager::get().loadScene(std::make_unique<Scene>());
		Registry& reg = SceneManager::get().active()->registry;
		Entity e = reg.createEntity();
		reg.addComponent<TransformComponent>(e, TransformComponent());
		reg.addComponent<MeshComponent>(e, MeshComponent{.meshID="cube", .materialID="simple"});

		Entity camEntity = reg.createEntity();
		reg.addComponent<TransformComponent>(camEntity, TransformComponent{.position=glm::vec3(0.0f,0.0f,5.0f)});
		reg.addComponent<CameraComponent>(camEntity, CameraComponent{.primary=true});
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
