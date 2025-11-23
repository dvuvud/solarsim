#include <engine/engine.hpp>
#include <engine/window.hpp>
#include <engine/renderer.hpp>

#include <systems/input_system.hpp>
#include <systems/physics_system.hpp>

#include <managers/scene_manager.hpp>
#include <scene/scene.hpp>

#include <components/transform_component.hpp>
#include <components/mesh_component.hpp>
#include <components/grid_component.hpp>
#include <components/camera_component.hpp>
#include <components/input_component.hpp>
#include <components/rigid_body_component.hpp>
#include <components/light_component.hpp>

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
		
		Entity grid = reg.createEntity();
		reg.addComponent<GridComponent>(grid, GridComponent{.meshID="grid", .materialID="grid"});

		Entity e1 = reg.createEntity();
		reg.addComponent<TransformComponent>(e1, TransformComponent{.scale=glm::vec3(5.0f)});
		reg.addComponent<MeshComponent>(e1, MeshComponent{.meshID="cube", .materialID="light"});
		reg.addComponent<RigidBodyComponent>(e1, RigidBodyComponent{.mass=10000.0f});
		reg.addComponent<LightComponent>(e1, LightComponent());

		Entity e2 = reg.createEntity();
		reg.addComponent<TransformComponent>(e2, TransformComponent{.position=glm::vec3(-50.0f,0.0f,3.0f), .scale=glm::vec3(3.0f)});
		reg.addComponent<MeshComponent>(e2, MeshComponent{.meshID="cube", .materialID="simple"});
		reg.addComponent<RigidBodyComponent>(e2, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-10.0f)});

		Entity camEntity = reg.createEntity();
		reg.addComponent<TransformComponent>(camEntity, TransformComponent{.position=glm::vec3(40.0f,50.0f,180.0f),
				.rotation=glm::quat(glm::vec3(glm::radians(-12.0f),glm::radians(12.0),0.0f))});
		reg.addComponent<CameraComponent>(camEntity, CameraComponent());
		reg.addComponent<InputComponent>(camEntity, InputComponent());
	}

	void Engine::run() {
		float deltaTime = 0.0f, lastFrame = (float)glfwGetTime();

		while (!m_window->shouldClose()) {
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (deltaTime > 0.1f)
				deltaTime = 0.0f;

			m_window->pollEvents();
			m_inputSystem->processInput(deltaTime);

			m_physicsSystem->update(deltaTime);

			m_renderer->render();

			m_window->swapBuffers();
		}
	}

	std::optional<Entity> Engine::getPrimaryCamera(Registry& registry) {
		for (auto e : registry.view<TransformComponent, CameraComponent>()) {
			auto& cam = registry.getComponent<CameraComponent>(e);
			if (cam.primary) return e;
		}
		return -1;
	}
}
