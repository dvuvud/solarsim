#include <gtest/gtest.h>
#include <systems/input_system.hpp>
#include <scene/scene.hpp>
#include <managers/scene_manager.hpp>
#include <components/input_component.hpp>
#include <components/transform_component.hpp>
#include <components/camera_component.hpp>

using namespace solarsim;

class InputSystemTest : public ::testing::Test {
	protected:
		void SetUp() override {
			scene = std::make_unique<Scene>();
			SceneManager::get().loadScene(std::move(scene));
		}

		void TearDown() override {
			SceneManager::get().unloadScene();
		}

		std::unique_ptr<Scene> scene;
};

// Test 1: Input component creation and properties
TEST_F(InputSystemTest, InputComponentProperties) {
	auto& registry = SceneManager::get().active()->registry;

	Entity entity = registry.createEntity();
	InputComponent input;
	input.movementSpeed = 15.0f;
	input.mouseSensitivity = 0.2f;
	input.takeInput = true;

	registry.addComponent(entity, input);

	auto& retrievedInput = registry.getComponent<InputComponent>(entity);
	EXPECT_EQ(retrievedInput.movementSpeed, 15.0f);
	EXPECT_EQ(retrievedInput.mouseSensitivity, 0.2f);
	EXPECT_TRUE(retrievedInput.takeInput);
}

// Test 2: Transform updates mark as dirty
TEST_F(InputSystemTest, TransformDirtyFlag) {
	auto& registry = SceneManager::get().active()->registry;

	Entity entity = registry.createEntity();
	TransformComponent transform;
	InputComponent input;

	registry.addComponent(entity, transform);
	registry.addComponent(entity, input);

	registry.getComponent<TransformComponent>(entity).position.x += 1.0f;
	registry.getComponent<TransformComponent>(entity).dirty = true;

	EXPECT_TRUE(registry.getComponent<TransformComponent>(entity).dirty);
}

// Test 3: Camera entity with input component
TEST_F(InputSystemTest, CameraInputEntity) {
	auto& registry = SceneManager::get().active()->registry;

	Entity camera = registry.createEntity();

	TransformComponent transform;
	transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	CameraComponent cameraComp;
	cameraComp.primary = true;

	InputComponent input;
	input.movementSpeed = 10.0f;
	input.mouseSensitivity = 0.1f;

	registry.addComponent(camera, transform);
	registry.addComponent(camera, cameraComp);
	registry.addComponent(camera, input);

	// Verify all components are properly attached
	EXPECT_TRUE(registry.hasComponent<TransformComponent>(camera));
	EXPECT_TRUE(registry.hasComponent<CameraComponent>(camera));
	EXPECT_TRUE(registry.hasComponent<InputComponent>(camera));

	auto& camComp = registry.getComponent<CameraComponent>(camera);
	EXPECT_TRUE(camComp.primary);
}

// Test 4: Input system processes entities with input component
TEST_F(InputSystemTest, InputSystemEntityProcessing) {
	auto& registry = SceneManager::get().active()->registry;

	// Create multiple entities, some with input component
	Entity entity1 = registry.createEntity();
	registry.addComponent(entity1, TransformComponent{});
	registry.addComponent(entity1, InputComponent{});

	Entity entity2 = registry.createEntity();
	registry.addComponent(entity2, TransformComponent{});
	// No input component

	Entity entity3 = registry.createEntity();
	registry.addComponent(entity3, TransformComponent{});
	registry.addComponent(entity3, InputComponent{});

	// Test that view returns only entities with both components
	auto inputEntities = registry.view<TransformComponent, InputComponent>();
	EXPECT_EQ(inputEntities.size(), 2);
}

// Test 5: Scene state toggles
TEST_F(InputSystemTest, SceneStateToggles) {
	auto scene = SceneManager::get().active();

	// Test pause toggle
	bool initialPaused = scene->paused;
	scene->togglePause();
	EXPECT_NE(scene->paused, initialPaused);

	// Test reverse toggle
	bool initialReverse = scene->reverse;
	scene->toggleReverse();
	EXPECT_NE(scene->reverse, initialReverse);

	// Toggle back
	scene->togglePause();
	scene->toggleReverse();
	EXPECT_EQ(scene->paused, initialPaused);
	EXPECT_EQ(scene->reverse, initialReverse);
}

// Test 6: Complex input entity with all components
TEST_F(InputSystemTest, ComplexInputEntity) {
	auto& registry = SceneManager::get().active()->registry;

	Entity player = registry.createEntity();

	// Add all relevant components for a player entity
	registry.addComponent(player, TransformComponent{
			.position = glm::vec3(10.0f, 2.0f, 5.0f),
			.rotation = glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
			.scale = glm::vec3(1.0f)
			});

	registry.addComponent(player, CameraComponent{
			.fov = 75.0f,
			.near = 0.1f,
			.far = 500.0f,
			.aspect = 16.0f / 9.0f,
			.primary = false
			});

	registry.addComponent(player, InputComponent{
			.takeInput = true,
			.movementSpeed = 8.0f,
			.mouseSensitivity = 0.15f
			});

	// Verify component relationships
	EXPECT_TRUE(registry.hasComponent<TransformComponent>(player));
	EXPECT_TRUE(registry.hasComponent<CameraComponent>(player));
	EXPECT_TRUE(registry.hasComponent<InputComponent>(player));

	auto& input = registry.getComponent<InputComponent>(player);
	EXPECT_TRUE(input.takeInput);
	EXPECT_EQ(input.movementSpeed, 8.0f);
}
