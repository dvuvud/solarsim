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
	Engine::Engine() 
		: m_window(800, 600, "solarsim"),
		m_inputSystem(m_window.getNativeWindow()),
		m_physicsSystem(),
		m_renderer()
	{
		init();
	}

	Engine::~Engine() {}

	void Engine::init() {
		SceneManager::get().loadScene(std::make_unique<Scene>());
		Registry& reg = SceneManager::get().active()->registry;

		Entity grid = reg.createEntity();
		reg.addComponent<GridComponent>(grid, GridComponent{.meshID="grid", .materialID="grid"});


		// ================================
		//     BINARY STAR SYSTEM DEMO
		// ================================
		/*
		Entity sun0 = reg.createEntity();
		reg.addComponent<TransformComponent>(sun0, TransformComponent{.position=glm::vec3(100.0f,0.0f,0.0f), .scale=glm::vec3(15.0f)});
		reg.addComponent<MeshComponent>(sun0, MeshComponent{.meshID="sphere", .materialID="sun"});
		reg.addComponent<RigidBodyComponent>(sun0, RigidBodyComponent{.mass=100'000.0f, .vel=glm::vec3(0.0f,0.0f,35.355f)});
		reg.addComponent<LightComponent>(sun0, LightComponent{.radius=700.0f});

		Entity sun1 = reg.createEntity();
		reg.addComponent<TransformComponent>(sun1, TransformComponent{.position=glm::vec3(-100.0f,0.0f,0.0f), .scale=glm::vec3(15.0f)});
		reg.addComponent<MeshComponent>(sun1, MeshComponent{.meshID="sphere", .materialID="sun"});
		reg.addComponent<RigidBodyComponent>(sun1, RigidBodyComponent{.mass=50'000.0f, .vel=glm::vec3(0.0f,0.0f,-70.71f)});
		reg.addComponent<LightComponent>(sun1, LightComponent{.radius=700.0f});
		*/
		// ================================
		// 	  SOLAR SYSTEM DEMO
		// ================================
		Entity sun = reg.createEntity();
		reg.addComponent<TransformComponent>(sun, TransformComponent{.scale=glm::vec3(15.0f)});
		reg.addComponent<MeshComponent>(sun, MeshComponent{.meshID="sphere", .materialID="sun"});
		reg.addComponent<RigidBodyComponent>(sun, RigidBodyComponent{.mass=100'000.0f});
		reg.addComponent<LightComponent>(sun, LightComponent{.radius=700.0f});

		Entity mercury = reg.createEntity();
		reg.addComponent<TransformComponent>(mercury, TransformComponent{.position=glm::vec3(-100.0f,0.0f,0.0f), .scale=glm::vec3(5.0f)});
		reg.addComponent<MeshComponent>(mercury, MeshComponent{.meshID="sphere", .materialID="mercury"});
		reg.addComponent<RigidBodyComponent>(mercury, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-100.0f)});

		Entity venus = reg.createEntity();
		reg.addComponent<TransformComponent>(venus, TransformComponent{.position=glm::vec3(-135.0f,0.0f,0.0f), .scale=glm::vec3(5.0f)});
		reg.addComponent<MeshComponent>(venus, MeshComponent{.meshID="sphere", .materialID="venus"});
		reg.addComponent<RigidBodyComponent>(venus, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-86.0f)});

		Entity earth = reg.createEntity();
		reg.addComponent<TransformComponent>(earth, TransformComponent{.position=glm::vec3(-175.0f,0.0f,0.0f), .scale=glm::vec3(5.0f)});
		reg.addComponent<MeshComponent>(earth, MeshComponent{.meshID="sphere", .materialID="earth"});
		reg.addComponent<RigidBodyComponent>(earth, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-75.5f)});

		Entity mars = reg.createEntity();
		reg.addComponent<TransformComponent>(mars, TransformComponent{.position=glm::vec3(-215.0f,0.0f,0.0f), .scale=glm::vec3(5.0f)});
		reg.addComponent<MeshComponent>(mars, MeshComponent{.meshID="sphere", .materialID="mars"});
		reg.addComponent<RigidBodyComponent>(mars, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-68.2f)});

		Entity jupiter = reg.createEntity();
		reg.addComponent<TransformComponent>(jupiter, TransformComponent{.position=glm::vec3(-285.0f,0.0f,0.0f), .scale=glm::vec3(15.0f)});
		reg.addComponent<MeshComponent>(jupiter, MeshComponent{.meshID="sphere", .materialID="jupiter"});
		reg.addComponent<RigidBodyComponent>(jupiter, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-59.3f)});

		Entity saturn = reg.createEntity();
		reg.addComponent<TransformComponent>(saturn, TransformComponent{.position=glm::vec3(-360.0f,0.0f,0.0f), .scale=glm::vec3(9.5f)});
		reg.addComponent<MeshComponent>(saturn, MeshComponent{.meshID="sphere", .materialID="saturn"});
		reg.addComponent<RigidBodyComponent>(saturn, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-52.7f)});

		Entity uranus = reg.createEntity();
		reg.addComponent<TransformComponent>(uranus, TransformComponent{.position=glm::vec3(-435.0f,0.0f,0.0f), .scale=glm::vec3(7.5f)});
		reg.addComponent<MeshComponent>(uranus, MeshComponent{.meshID="sphere", .materialID="uranus"});
		reg.addComponent<RigidBodyComponent>(uranus, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-48.0f)});

		Entity neptune = reg.createEntity();
		reg.addComponent<TransformComponent>(neptune, TransformComponent{.position=glm::vec3(-500.0f,0.0f,0.0f), .scale=glm::vec3(7.5f)});
		reg.addComponent<MeshComponent>(neptune, MeshComponent{.meshID="sphere", .materialID="neptune"});
		reg.addComponent<RigidBodyComponent>(neptune, RigidBodyComponent{.mass=100.0f, .vel=glm::vec3(0.0f,0.0f,-44.7f)});

		Entity camEntity = reg.createEntity();
		reg.addComponent<TransformComponent>(camEntity, TransformComponent{.position=glm::vec3(0.0f,300.0f,1000.0f),
				.rotation=glm::quat(glm::vec3(glm::radians(-17.0f),0.0f,0.0f))});
		reg.addComponent<CameraComponent>(camEntity, CameraComponent());
		reg.addComponent<InputComponent>(camEntity, InputComponent());
	}

	void Engine::run() {
		const float maxDelta = 1.0f / 30.0f; // clamp to ~30 fps
		float deltaTime = 0.0f, lastFrame = (float)glfwGetTime();

		while (!m_window.shouldClose()) {
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (deltaTime > 0.1f)
				deltaTime = 0.0f;
			if (deltaTime > maxDelta)
				deltaTime = maxDelta;

			m_window.pollEvents();
			m_inputSystem.processInput(deltaTime);

			m_physicsSystem.update(deltaTime);

			m_renderer.render();

			m_window.swapBuffers();
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
