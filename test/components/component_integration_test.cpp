#include <gtest/gtest.h>
#include <scene/scene.hpp>
#include <scene/registry.hpp>
#include <components/transform_component.hpp>
#include <components/rigid_body_component.hpp>
#include <components/mesh_component.hpp>
#include <components/light_component.hpp>
#include <components/camera_component.hpp>
#include <components/input_component.hpp>
#include <components/grid_component.hpp>

using namespace solarsim;

class ComponentIntegrationTest : public ::testing::Test {
	protected:
		void SetUp() override {
			scene = std::make_unique<Scene>();
		}

		void TearDown() override {
			scene.reset();
		}

		std::unique_ptr<Scene> scene;
};

// Test 1: Camera entity setup
TEST_F(ComponentIntegrationTest, CameraEntity) {
	auto& registry = scene->registry;

	Entity camera = registry.createEntity();

	registry.addComponent(camera, TransformComponent{
			.position = glm::vec3(40.0f, 50.0f, 180.0f),
			.rotation = glm::quat(glm::vec3(glm::radians(-12.0f), glm::radians(12.0f), 0.0f))
			});

	registry.addComponent(camera, CameraComponent{
			.fov = 45.0f,
			.near = 0.1f,
			.far = 1000.0f,
			.aspect = 800.0f / 600.0f,
			.primary = true
			});

	registry.addComponent(camera, InputComponent{
			.takeInput = true,
			.movementSpeed = 100.0f,
			.mouseSensitivity = 0.1f
			});

	// Verify camera is primary
	auto& camComp = registry.getComponent<CameraComponent>(camera);
	EXPECT_TRUE(camComp.primary);
	EXPECT_EQ(camComp.fov, 45.0f);

	// Verify input settings
	auto& inputComp = registry.getComponent<InputComponent>(camera);
	EXPECT_TRUE(inputComp.takeInput);
	EXPECT_EQ(inputComp.movementSpeed, 100.0f);
}

// Test 2: Grid entity setup
TEST_F(ComponentIntegrationTest, GridEntity) {
	auto& registry = scene->registry;

	Entity grid = registry.createEntity();

	registry.addComponent(grid, GridComponent{
			.meshID = "grid",
			.materialID = "grid"
			});

	auto& gridComp = registry.getComponent<GridComponent>(grid);
	EXPECT_EQ(gridComp.meshID, "grid");
	EXPECT_EQ(gridComp.materialID, "grid");
}

// Test 3: Complex entity with physics and rendering
TEST_F(ComponentIntegrationTest, PhysicsRenderingEntity) {
	auto& registry = scene->registry;

	Entity celestialBody = registry.createEntity();

	// Physics components
	registry.addComponent(celestialBody, TransformComponent{
			.position = glm::vec3(100.0f, 0.0f, 0.0f),
			.scale = glm::vec3(5.0f)
			});

	registry.addComponent(celestialBody, RigidBodyComponent{
			.mass = 5000.0f,
			.vel = glm::vec3(0.0f, 25.0f, 0.0f),
			.useGravity = true
			});

	// Rendering components
	registry.addComponent(celestialBody, MeshComponent{
			.meshID = "cube",
			.materialID = "simple"
			});

	// Verify all components work together
	EXPECT_TRUE(registry.hasComponent<TransformComponent>(celestialBody));
	EXPECT_TRUE(registry.hasComponent<RigidBodyComponent>(celestialBody));
	EXPECT_TRUE(registry.hasComponent<MeshComponent>(celestialBody));

	auto& transform = registry.getComponent<TransformComponent>(celestialBody);
	auto& rigidbody = registry.getComponent<RigidBodyComponent>(celestialBody);
	auto& mesh = registry.getComponent<MeshComponent>(celestialBody);

	EXPECT_EQ(transform.position, glm::vec3(100.0f, 0.0f, 0.0f));
	EXPECT_EQ(rigidbody.mass, 5000.0f);
	EXPECT_EQ(mesh.meshID, "cube");
}

// Test 4: Light source entity
TEST_F(ComponentIntegrationTest, LightSourceEntity) {
	auto& registry = scene->registry;

	Entity light = registry.createEntity();

	registry.addComponent(light, TransformComponent{
			.position = glm::vec3(0.0f, 10.0f, 0.0f)
			});

	registry.addComponent(light, LightComponent{
			.color = glm::vec3(1.0f, 0.9f, 0.8f),
			.radius = 200.0f
			});

	registry.addComponent(light, MeshComponent{
			.meshID = "cube",
			.materialID = "light"
			});

	auto& lightComp = registry.getComponent<LightComponent>(light);
	EXPECT_EQ(lightComp.color, glm::vec3(1.0f, 0.9f, 0.8f));
	EXPECT_EQ(lightComp.radius, 200.0f);
}
