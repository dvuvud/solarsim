#include <gtest/gtest.h>
#include <scene/scene.hpp>
#include <scene/registry.hpp>
#include <components/transform_component.hpp>
#include <components/rigid_body_component.hpp>
#include <components/mesh_component.hpp>
#include <components/light_component.hpp>
#include <components/camera_component.hpp>

using namespace solarsim;

class SceneTest : public ::testing::Test {
	protected:
		void SetUp() override {
			scene = std::make_unique<Scene>();
		}

		void TearDown() override {
			scene.reset();
		}

		std::unique_ptr<Scene> scene;
};

// Test 1: Scene state management
TEST_F(SceneTest, StateManagement) {
	EXPECT_FALSE(scene->paused);
	EXPECT_FALSE(scene->reverse);

	scene->togglePause();
	EXPECT_TRUE(scene->paused);

	scene->toggleReverse();
	EXPECT_TRUE(scene->reverse);

	scene->togglePause();
	EXPECT_FALSE(scene->paused);

	scene->toggleReverse();
	EXPECT_FALSE(scene->reverse);
}

// Test 2: Entity management through scene registry
TEST_F(SceneTest, EntityManagement) {
	auto& registry = scene->registry;

	Entity e1 = registry.createEntity();
	Entity e2 = registry.createEntity();

	// Add different component combinations
	registry.addComponent(e1, TransformComponent{});
	registry.addComponent(e1, RigidBodyComponent{});

	registry.addComponent(e2, TransformComponent{});
	registry.addComponent(e2, MeshComponent{});
	registry.addComponent(e2, LightComponent{});

	// Test component views
	auto transformOnly = registry.view<TransformComponent>();
	EXPECT_EQ(transformOnly.size(), 2);

	auto transformRigidBody = registry.view<TransformComponent, RigidBodyComponent>();
	EXPECT_EQ(transformRigidBody.size(), 1);

	auto transformMeshLight = registry.view<TransformComponent, MeshComponent, LightComponent>();
	EXPECT_EQ(transformMeshLight.size(), 1);
}

// Test 3: Time scale affects physics
TEST_F(SceneTest, TimeScale) {
	scene->timeScale = 2.0f; // Double speed

	auto& registry = scene->registry;

	Entity entity = registry.createEntity();

	TransformComponent t;
	t.position = glm::vec3(0.0f, 0.0f, 0.0f);

	RigidBodyComponent rb;
	rb.mass = 1000.0f;
	rb.vel = glm::vec3(10.0f, 0.0f, 0.0f);

	registry.addComponent(entity, t);
	registry.addComponent(entity, rb);

	EXPECT_EQ(scene->timeScale, 2.0f);
}

// Test 4: Complex entity composition
TEST_F(SceneTest, ComplexEntityComposition) {
	auto& registry = scene->registry;

	// Create a sun-like entity
	Entity sun = registry.createEntity();
	registry.addComponent(sun, TransformComponent{
			.position = glm::vec3(0.0f, 0.0f, 0.0f),
			.scale = glm::vec3(15.0f)
			});
	registry.addComponent(sun, RigidBodyComponent{
			.mass = 10000.0f
			});
	registry.addComponent(sun, MeshComponent{
			.meshID = "cube",
			.materialID = "light"
			});
	registry.addComponent(sun, LightComponent{
			.color = glm::vec3(1.0f, 1.0f, 0.8f),
			.radius = 135.0f
			});

	// Create a planet-like entity
	Entity planet = registry.createEntity();
	registry.addComponent(planet, TransformComponent{
			.position = glm::vec3(-50.0f, 0.0f, 3.0f),
			.scale = glm::vec3(3.0f)
			});
	registry.addComponent(planet, RigidBodyComponent{
			.mass = 100.0f,
			.vel = glm::vec3(0.0f, 0.0f, -35.0f)
			});
	registry.addComponent(planet, MeshComponent{
			.meshID = "cube", 
			.materialID = "simple"
			});

	// Verify all components are present
	EXPECT_TRUE(registry.hasComponent<TransformComponent>(sun));
	EXPECT_TRUE(registry.hasComponent<RigidBodyComponent>(sun));
	EXPECT_TRUE(registry.hasComponent<MeshComponent>(sun));
	EXPECT_TRUE(registry.hasComponent<LightComponent>(sun));

	EXPECT_TRUE(registry.hasComponent<TransformComponent>(planet));
	EXPECT_TRUE(registry.hasComponent<RigidBodyComponent>(planet));
	EXPECT_TRUE(registry.hasComponent<MeshComponent>(planet));
	EXPECT_FALSE(registry.hasComponent<LightComponent>(planet));
}
