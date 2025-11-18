#include <gtest/gtest.h>
#include <simulation/entity.hpp>

using namespace solarsim;

class EntityTest : public ::testing::Test {
	protected:
		void SetUp() override {
			Transform transform;
			transform.position = glm::vec3(1.0f, 2.0f, 3.0f);
			transform.rotation = glm::vec3(45.0f, 90.0f, 180.0f);
			transform.scale = glm::vec3(2.0f, 2.0f, 2.0f);

			entity = std::make_unique<Entity>(transform, 10.0f, 5.0f);
		}

		void TearDown() override {
			entity.reset();
		}

		std::unique_ptr<Entity> entity;
};

// Test 1: Entity construction and basic properties
TEST_F(EntityTest, Construction) {
	EXPECT_EQ(entity->getMass(), 10.0f);
	EXPECT_EQ(entity->getRadius(), 5.0f);
	EXPECT_EQ(entity->getPosition(), glm::vec3(1.0f, 2.0f, 3.0f));
}

// Test 2: Transform getters and setters
TEST_F(EntityTest, TransformGettersAndSetters) {
	entity->setPosition(glm::vec3(5.0f, 6.0f, 7.0f));
	EXPECT_EQ(entity->getPosition(), glm::vec3(5.0f, 6.0f, 7.0f));

	entity->setRotation(glm::vec3(10.0f, 20.0f, 30.0f));
	EXPECT_EQ(entity->getRotation(), glm::vec3(10.0f, 20.0f, 30.0f));

	entity->setScale(glm::vec3(3.0f, 3.0f, 3.0f));
	EXPECT_EQ(entity->getScale(), glm::vec3(3.0f, 3.0f, 3.0f));
}

// Test 3: Velocity management
TEST_F(EntityTest, VelocityManagement) {
	entity->setVelocity(glm::vec3(10.0f, 0.0f, 0.0f));
	EXPECT_EQ(entity->getVelocity(), glm::vec3(10.0f, 0.0f, 0.0f));
}

// Test 4: Force application and physics update
TEST_F(EntityTest, PhysicsUpdate) {
	entity->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	entity->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	entity->applyForce(glm::vec3(10.0f, 0.0f, 0.0f));
	entity->update(1.0f);

	EXPECT_NEAR(entity->getVelocity().x, 1.0f, 0.001f);
	EXPECT_NEAR(entity->getPosition().x, 1.0f, 0.001f);
}

// Test 5: Transform model matrix calculation
TEST(TransformTest, ModelMatrixCalculation) {
	Transform transform;
	transform.position = glm::vec3(2.0f, 3.0f, 4.0f);
	transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 model = transform.getModelMatrix();

	glm::mat4 expected = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_NEAR(model[i][j], expected[i][j], 0.001f);
		}
	}
}
