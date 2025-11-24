#include <gtest/gtest.h>
#include <scene/registry.hpp>
#include <components/transform_component.hpp>
#include <components/rigid_body_component.hpp>
#include <components/mesh_component.hpp>

using namespace solarsim;

class RegistryTest : public ::testing::Test {
	protected:
		void SetUp() override {
			registry = std::make_unique<Registry>();
		}

		void TearDown() override {
			registry.reset();
		}

		std::unique_ptr<Registry> registry;
};

// Test 1: Entity creation
TEST_F(RegistryTest, EntityCreation) {
	Entity e1 = registry->createEntity();
	Entity e2 = registry->createEntity();

	EXPECT_NE(e1, e2);
	EXPECT_GE(e2, e1);
}

// Test 2: Component addition and retrieval
TEST_F(RegistryTest, ComponentManagement) {
	Entity entity = registry->createEntity();

	TransformComponent transform;
	transform.position = glm::vec3(1.0f, 2.0f, 3.0f);
	transform.scale = glm::vec3(2.0f, 2.0f, 2.0f);

	registry->addComponent(entity, transform);

	EXPECT_TRUE(registry->hasComponent<TransformComponent>(entity));

	auto& retrievedTransform = registry->getComponent<TransformComponent>(entity);
	EXPECT_EQ(retrievedTransform.position, glm::vec3(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(retrievedTransform.scale, glm::vec3(2.0f, 2.0f, 2.0f));
}

// Test 3: Multiple components on single entity
TEST_F(RegistryTest, MultipleComponents) {
	Entity entity = registry->createEntity();

	TransformComponent transform;
	transform.position = glm::vec3(1.0f, 2.0f, 3.0f);

	RigidBodyComponent rb;
	rb.mass = 10.0f;
	rb.vel = glm::vec3(5.0f, 0.0f, 0.0f);

	registry->addComponent(entity, transform);
	registry->addComponent(entity, rb);

	EXPECT_TRUE(registry->hasComponent<TransformComponent>(entity));
	EXPECT_TRUE(registry->hasComponent<RigidBodyComponent>(entity));
	EXPECT_EQ(registry->getComponent<RigidBodyComponent>(entity).mass, 10.0f);
}

// Test 4: Component view functionality
TEST_F(RegistryTest, ComponentView) {
	Entity e1 = registry->createEntity();
	Entity e2 = registry->createEntity();
	Entity e3 = registry->createEntity();

	// Add transform to all entities
	registry->addComponent(e1, TransformComponent{});
	registry->addComponent(e2, TransformComponent{});
	registry->addComponent(e3, TransformComponent{});

	// Add rigid body to only e1 and e2
	registry->addComponent(e1, RigidBodyComponent{});
	registry->addComponent(e2, RigidBodyComponent{});

	auto entitiesWithBoth = registry->view<TransformComponent, RigidBodyComponent>();
	EXPECT_EQ(entitiesWithBoth.size(), 2);

	auto entitiesWithTransform = registry->view<TransformComponent>();
	EXPECT_EQ(entitiesWithTransform.size(), 3);
}
