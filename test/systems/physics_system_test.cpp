#include <gtest/gtest.h>
#include <systems/physics_system.hpp>
#include <scene/scene.hpp>
#include <managers/scene_manager.hpp>
#include <components/transform_component.hpp>
#include <components/rigid_body_component.hpp>

using namespace solarsim;

class PhysicsSystemTest : public ::testing::Test {
	protected:
		void SetUp() override {
			physicsSystem = std::make_unique<PhysicsSystem>();
			scene = std::make_unique<Scene>();
			SceneManager::get().loadScene(std::move(scene));
		}

		void TearDown() override {
			SceneManager::get().unloadScene();
			physicsSystem.reset();
		}

		std::unique_ptr<PhysicsSystem> physicsSystem;
		std::unique_ptr<Scene> scene;
};

// Test 1: Basic gravity calculation between two bodies
TEST_F(PhysicsSystemTest, GravityBetweenTwoBodies) {
	auto& registry = SceneManager::get().active()->registry;

	Entity e1 = registry.createEntity();
	Entity e2 = registry.createEntity();

	TransformComponent t1, t2;
	t1.position = glm::vec3(0.0f, 0.0f, 0.0f);
	t2.position = glm::vec3(10.0f, 0.0f, 0.0f);

	RigidBodyComponent rb1, rb2;
	rb1.mass = 1000.0f;
	rb2.mass = 1000.0f;
	rb1.vel = glm::vec3(0.0f);
	rb2.vel = glm::vec3(0.0f);

	registry.addComponent(e1, t1);
	registry.addComponent(e1, rb1);
	registry.addComponent(e2, t2);
	registry.addComponent(e2, rb2);

	glm::vec3 initialPos1 = registry.getComponent<TransformComponent>(e1).position;
	glm::vec3 initialPos2 = registry.getComponent<TransformComponent>(e2).position;

	physicsSystem->update(1.0f);

	glm::vec3 newPos1 = registry.getComponent<TransformComponent>(e1).position;
	glm::vec3 newPos2 = registry.getComponent<TransformComponent>(e2).position;

	EXPECT_NE(newPos1, initialPos1);
	EXPECT_NE(newPos2, initialPos2);

	// Check that positions are valid
	EXPECT_FALSE(glm::any(glm::isnan(newPos1)));
	EXPECT_FALSE(glm::any(glm::isnan(newPos2)));
}

// Test 2: Physics respects pause state
TEST_F(PhysicsSystemTest, PhysicsPause) {
	auto& registry = SceneManager::get().active()->registry;
	SceneManager::get().active()->paused = true;

	Entity entity = registry.createEntity();

	TransformComponent t;
	t.position = glm::vec3(0.0f, 0.0f, 0.0f);

	RigidBodyComponent rb;
	rb.mass = 1000.0f;
	rb.vel = glm::vec3(10.0f, 0.0f, 0.0f);

	registry.addComponent(entity, t);
	registry.addComponent(entity, rb);

	glm::vec3 initialPos = registry.getComponent<TransformComponent>(entity).position;

	physicsSystem->update(1.0f);

	glm::vec3 newPos = registry.getComponent<TransformComponent>(entity).position;

	// Should not move when paused
	EXPECT_EQ(newPos, initialPos);
}

// Test 3: Time reversal
TEST_F(PhysicsSystemTest, TimeReversal) {
	auto& registry = SceneManager::get().active()->registry;

	Entity entity = registry.createEntity();

	TransformComponent t;
	t.position = glm::vec3(0.0f, 0.0f, 0.0f);

	RigidBodyComponent rb;
	rb.mass = 1000.0f;
	rb.vel = glm::vec3(10.0f, 0.0f, 0.0f); // Simple velocity

	registry.addComponent(entity, t);
	registry.addComponent(entity, rb);

	glm::vec3 initialPos = registry.getComponent<TransformComponent>(entity).position;

	// Move forward first
	SceneManager::get().active()->reverse = false;
	physicsSystem->update(1.0f);
	glm::vec3 forwardPos = registry.getComponent<TransformComponent>(entity).position;

	EXPECT_NE(forwardPos, initialPos);
	EXPECT_FALSE(glm::any(glm::isnan(forwardPos)));

	// Then reverse
	SceneManager::get().active()->reverse = true;
	physicsSystem->update(1.0f);
	glm::vec3 reversedPos = registry.getComponent<TransformComponent>(entity).position;

	EXPECT_FALSE(glm::any(glm::isnan(reversedPos)));

	float distFromStart = glm::length(reversedPos - initialPos);
	float distFromForward = glm::length(reversedPos - forwardPos);

	// With reversal, we should be closer to start than to forward position
	EXPECT_LT(distFromStart, distFromForward);
}

// Test 4: Mass affects acceleration with valid setup
TEST_F(PhysicsSystemTest, MassEffect) {
	auto& registry = SceneManager::get().active()->registry;

	Entity heavy = registry.createEntity();
	Entity light = registry.createEntity();

	TransformComponent t1, t2;
	t1.position = glm::vec3(0.0f, 0.0f, 0.0f);
	t2.position = glm::vec3(0.0f, 0.0f, 20.0f); // Sufficient distance

	RigidBodyComponent rb1, rb2;
	rb1.mass = 10000.0f;
	rb2.mass = 100.0f;
	rb1.vel = glm::vec3(0.0f);
	rb2.vel = glm::vec3(0.0f);

	registry.addComponent(heavy, t1);
	registry.addComponent(heavy, rb1);
	registry.addComponent(light, t2);
	registry.addComponent(light, rb2);

	glm::vec3 initialHeavyPos = registry.getComponent<TransformComponent>(heavy).position;
	glm::vec3 initialLightPos = registry.getComponent<TransformComponent>(light).position;

	physicsSystem->update(1.0f);

	glm::vec3 newHeavyPos = registry.getComponent<TransformComponent>(heavy).position;
	glm::vec3 newLightPos = registry.getComponent<TransformComponent>(light).position;

	// Check for valid positions
	EXPECT_FALSE(glm::any(glm::isnan(newHeavyPos)));
	EXPECT_FALSE(glm::any(glm::isnan(newLightPos)));

	// Both should have moved
	EXPECT_NE(newHeavyPos, initialHeavyPos);
	EXPECT_NE(newLightPos, initialLightPos);

	// Lighter object should move more
	float heavyMovement = glm::length(newHeavyPos - initialHeavyPos);
	float lightMovement = glm::length(newLightPos - initialLightPos);

	EXPECT_GT(lightMovement, heavyMovement);
}
