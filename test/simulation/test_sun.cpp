#include <gtest/gtest.h>
#include <simulation/sun.hpp>
#include <memory>

using namespace solarsim;

class SunTest : public ::testing::Test {
	protected:
		void SetUp() override {
			Transform transform;
			transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

			sun = std::make_unique<Sun>(transform, 1.989e30f, 696340.0f, 1000.0f, glm::vec3(1.0f, 1.0f, 0.8f), glm::vec3(0.0f));
		}

		void TearDown() override {
			sun.reset();
		}

		std::unique_ptr<Sun> sun;
};

// Test 1: Sun construction with basic parameters
TEST_F(SunTest, BasicConstruction) {
	Transform transform;
	transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	Sun sun(transform, 1.0e30f, 500000.0f, 800.0f, glm::vec3(1.0f, 0.9f, 0.8f), glm::vec3(0.0f));

	EXPECT_EQ(sun.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(sun.getMass(), 1.0e30f);
	EXPECT_EQ(sun.getRadius(), 500000.0f);
	EXPECT_EQ(sun.getLightRadius(), 800.0f);
	EXPECT_EQ(sun.getLightColor(), glm::vec3(1.0f, 0.9f, 0.8f));
	EXPECT_EQ(sun.getVelocity(), glm::vec3(0.0f));
}

// Test 2: Sun light properties
TEST_F(SunTest, LightProperties) {
	EXPECT_LT(sun->getLightRadius(), sun->getRadius());
	EXPECT_EQ(sun->getLightColor(), glm::vec3(1.0f, 1.0f, 0.8f));

	Transform transform;
	Sun blueSun(transform, 1.0e29f, 10000.0f, 50000.0f, glm::vec3(0.7f, 0.8f, 1.0f));
	EXPECT_EQ(blueSun.getLightColor(), glm::vec3(0.7f, 0.8f, 1.0f));
}

// Test 3: Sun as stationary massive object
TEST_F(SunTest, StationaryMassiveObject) {
	glm::vec3 initialPosition = sun->getPosition();

	sun->applyForce(glm::vec3(1.0e25f, 0.0f, 0.0f));
	sun->update(1.0f);

	glm::vec3 newPosition = sun->getPosition();
	float movement = glm::length(newPosition - initialPosition);
	EXPECT_LT(movement, 0.001f);
}

// Test 4: Sun with velocity
TEST_F(SunTest, MovingSun) {
	sun->setVelocity(glm::vec3(10.0f, 0.0f, 0.0f));

	EXPECT_EQ(sun->getVelocity(), glm::vec3(10.0f, 0.0f, 0.0f));

	glm::vec3 initialPos = sun->getPosition();
	sun->update(1.0f);
	glm::vec3 newPos = sun->getPosition();

	EXPECT_NE(newPos, initialPos);
	EXPECT_NEAR(newPos.x, 10.0f, 0.001f);
}
