#include <gtest/gtest.h>
#include <simulation/planet.hpp>
#include <mesh/cube.hpp>
#include <graphics/material.hpp>
#include <memory>

using namespace solarsim;

class PlanetTest : public ::testing::Test {
	protected:
		void SetUp() override {
			Transform transform;
			transform.position = glm::vec3(10.0f, 0.0f, 0.0f);

			planet = std::make_unique<Planet>(transform, 5.97e24f, 6371.0f, glm::vec3(0.0f, 29.78f, 0.0f));
		}

		void TearDown() override {
			planet.reset();
		}

		std::unique_ptr<Planet> planet;
};

// Test 1: Planet construction with basic parameters
TEST_F(PlanetTest, BasicConstruction) {
	Transform transform;
	transform.position = glm::vec3(5.0f, 0.0f, 0.0f);

	Planet planet(transform, 1.0e24f, 1000.0f, glm::vec3(0.0f, 10.0f, 0.0f));

	EXPECT_EQ(planet.getPosition(), glm::vec3(5.0f, 0.0f, 0.0f));
	EXPECT_EQ(planet.getMass(), 1.0e24f);
	EXPECT_EQ(planet.getRadius(), 1000.0f);
	EXPECT_EQ(planet.getVelocity(), glm::vec3(0.0f, 10.0f, 0.0f));
}

// Test 2: Planet orbital mechanics
TEST_F(PlanetTest, OrbitalMechanics) {
	glm::vec3 initialPosition = planet->getPosition();
	glm::vec3 initialVelocity = planet->getVelocity();

	// Simulate gravitational pull
	glm::vec3 gravityForce = -glm::normalize(initialPosition) * 1.0e20f;
	planet->applyForce(gravityForce);
	planet->update(1.0f);

	// Position and velocity should change
	EXPECT_NE(planet->getPosition(), initialPosition);
	EXPECT_NE(planet->getVelocity(), initialVelocity);
}

// Test 3: Multiple planets with different initial velocities
TEST_F(PlanetTest, MultiplePlanetsDifferentVelocities) {
	Transform earthTransform, marsTransform;
	earthTransform.position = glm::vec3(149.6f, 0.0f, 0.0f);
	marsTransform.position = glm::vec3(227.9f, 0.0f, 0.0f);

	Planet earth(earthTransform, 5.97e24f, 6371.0f, glm::vec3(0.0f, 29.78f, 0.0f));
	Planet mars(marsTransform, 6.39e23f, 3389.5f, glm::vec3(0.0f, 24.07f, 0.0f));

	EXPECT_NE(earth.getVelocity(), mars.getVelocity());
	EXPECT_NE(earth.getMass(), mars.getMass());
}
