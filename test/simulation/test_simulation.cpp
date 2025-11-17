#include <gtest/gtest.h>
#include <simulation/simulation.hpp>
#include <simulation/sun.hpp>
#include <simulation/planet.hpp>
#include <memory>

using namespace solarsim;

class SimulationTest : public ::testing::Test {
	protected:
		void SetUp() override {
			simulation = std::make_unique<Simulation>(false);
		}

		void TearDown() override {
			simulation.reset();
		}

		std::unique_ptr<Simulation> simulation;
};

// Test 1: Simulation construction and initial state
TEST_F(SimulationTest, InitialState) {
	EXPECT_EQ(simulation->getEntityCount(), 0);
	EXPECT_EQ(simulation->getSun(), nullptr);
	EXPECT_TRUE(simulation->getPlanets().empty());
	EXPECT_NE(simulation->getCamera(), nullptr);
	EXPECT_EQ(simulation->getGrid(), nullptr);
}

// Test 2: Spawn Sun entity
TEST_F(SimulationTest, SpawnSun) {
	Transform sunTransform;
	sunTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	auto sun = std::make_unique<Sun>(sunTransform, 1.989e30f, 696340.0f, 1000.0f);
	simulation->spawnEntity(std::move(sun));

	EXPECT_EQ(simulation->getEntityCount(), 1);
	EXPECT_NE(simulation->getSun(), nullptr);
	EXPECT_TRUE(simulation->getPlanets().empty());
}

// Test 3: Spawn Planet entity
TEST_F(SimulationTest, SpawnPlanet) {
	Transform planetTransform;
	planetTransform.position = glm::vec3(10.0f, 0.0f, 0.0f);

	auto planet = std::make_unique<Planet>(planetTransform, 5.97e24f, 6371.0f);
	simulation->spawnEntity(std::move(planet));

	EXPECT_EQ(simulation->getEntityCount(), 1);
	EXPECT_EQ(simulation->getSun(), nullptr);
	EXPECT_EQ(simulation->getPlanets().size(), 1);
}

// Test 4: Spawn multiple entities (Sun and Planets)
TEST_F(SimulationTest, SpawnMultipleEntities) {
	Transform sunTransform;
	sunTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	auto sun = std::make_unique<Sun>(sunTransform, 1.989e30f, 696340.0f, 1000.0f);
	simulation->spawnEntity(std::move(sun));

	Transform earthTransform;
	earthTransform.position = glm::vec3(149.6f, 0.0f, 0.0f);
	auto earth = std::make_unique<Planet>(earthTransform, 5.97e24f, 6371.0f, glm::vec3(0.0f, 29.78f, 0.0f));
	simulation->spawnEntity(std::move(earth));

	Transform marsTransform;
	marsTransform.position = glm::vec3(227.9f, 0.0f, 0.0f);
	auto mars = std::make_unique<Planet>(marsTransform, 6.39e23f, 3389.5f, glm::vec3(0.0f, 24.07f, 0.0f));
	simulation->spawnEntity(std::move(mars));

	EXPECT_EQ(simulation->getEntityCount(), 3);
	EXPECT_NE(simulation->getSun(), nullptr);
	EXPECT_EQ(simulation->getPlanets().size(), 2);
}

// Test 5: Gravity force calculation between two planets
TEST_F(SimulationTest, GravityForceCalculation) {
	Transform transform1, transform2;
	transform1.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform2.position = glm::vec3(10.0f, 0.0f, 0.0f);

	auto planet1 = std::make_unique<Planet>(transform1, 1000.0f, 1.0f);
	auto planet2 = std::make_unique<Planet>(transform2, 1000.0f, 1.0f);

	glm::vec3 initialVel1 = planet1->getVelocity();
	glm::vec3 initialVel2 = planet2->getVelocity();

	simulation->spawnEntity(std::move(planet1));
	simulation->spawnEntity(std::move(planet2));

	simulation->calculateGravityForces();

	simulation->update(1.0f);

	const auto& entities = simulation->getEntities();
	EXPECT_EQ(entities.size(), 2);

	EXPECT_NE(entities[0]->getVelocity(), initialVel1);
	EXPECT_NE(entities[1]->getVelocity(), initialVel2);
}

// Test 6: Time reversal functionality
TEST_F(SimulationTest, TimeReversal) {
	Transform planetTransform;
	planetTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	auto planet = std::make_unique<Planet>(planetTransform, 1000.0f, 1.0f, glm::vec3(10.0f, 0.0f, 0.0f));
	simulation->spawnEntity(std::move(planet));

	const auto& entities = simulation->getEntities();
	glm::vec3 initialPosition = entities[0]->getPosition();

	simulation->update(1.0f);
	glm::vec3 forwardPosition = entities[0]->getPosition();

	EXPECT_NE(forwardPosition, initialPosition);

	simulation->toggleReverse();

	simulation->update(1.0f);
	glm::vec3 reversedPosition = entities[0]->getPosition();

	float distanceFromStart = glm::length(reversedPosition - initialPosition);
	float distanceFromForward = glm::length(reversedPosition - forwardPosition);

	EXPECT_GT(distanceFromForward, distanceFromStart);
}

// Test 7: Clear all entities
TEST_F(SimulationTest, ClearEntities) {
	Transform transform;
	auto sun = std::make_unique<Sun>(transform, 1.0e30f, 1000.0f, 500.0f);
	auto planet = std::make_unique<Planet>(transform, 1.0e24f, 100.0f);

	simulation->spawnEntity(std::move(sun));
	simulation->spawnEntity(std::move(planet));

	EXPECT_EQ(simulation->getEntityCount(), 2);

	simulation->clearAllEntities();

	EXPECT_EQ(simulation->getEntityCount(), 0);
	EXPECT_EQ(simulation->getSun(), nullptr);
	EXPECT_TRUE(simulation->getPlanets().empty());
}

// Test 8: Orbital mechanics simulation
TEST_F(SimulationTest, OrbitalMechanics) {
	Transform sunTransform;
	sunTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	auto sun = std::make_unique<Sun>(sunTransform, 1.989e5f, 696340.0f, 1000.0f);

	Transform planetTransform;
	planetTransform.position = glm::vec3(100.0f, 0.0f, 0.0f);
	auto planet = std::make_unique<Planet>(planetTransform, 5.97e2f, 6371.0f, glm::vec3(0.0f, 10.0f, 0.0f));

	simulation->spawnEntity(std::move(sun));
	simulation->spawnEntity(std::move(planet));

	const auto& entities = simulation->getEntities();
	glm::vec3 initialSunPos = entities[0]->getPosition();
	glm::vec3 initialPlanetPos = entities[1]->getPosition();

	for (int i = 0; i < 10; ++i) {
		simulation->update(0.1f);
	}

	EXPECT_NE(entities[0]->getPosition(), initialSunPos);
	EXPECT_NE(entities[1]->getPosition(), initialPlanetPos);

	float sunMovement = glm::length(entities[0]->getPosition() - initialSunPos);
	float planetMovement = glm::length(entities[1]->getPosition() - initialPlanetPos);
	EXPECT_LT(sunMovement, planetMovement);
}

// Test 9: Minimum distance clamping in gravity calculation
TEST_F(SimulationTest, MinimumDistanceClamping) {
	Transform transform1, transform2;
	transform1.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform2.position = glm::vec3(1.0f, 0.0f, 0.0f); // Within MIN_DISTANCE (1.5f)

	auto planet1 = std::make_unique<Planet>(transform1, 1000.0f, 1.0f);
	auto planet2 = std::make_unique<Planet>(transform2, 1000.0f, 1.0f);

	simulation->spawnEntity(std::move(planet1));
	simulation->spawnEntity(std::move(planet2));

	const auto& entities = simulation->getEntities();
	glm::vec3 initialVel1 = entities[0]->getVelocity();
	glm::vec3 initialVel2 = entities[1]->getVelocity();

	simulation->calculateGravityForces();
	simulation->update(1.0f);

	// Velocities should remain unchanged (due tolimiting minimum distance)
	EXPECT_EQ(entities[0]->getVelocity(), initialVel1);
	EXPECT_EQ(entities[1]->getVelocity(), initialVel2);
}

// Test 10: Entity type categorization
TEST_F(SimulationTest, EntityCategorization) {
	Transform transform;

	auto sun = std::make_unique<Sun>(transform, 1.0e30f, 1000.0f, 500.0f);
	auto planet1 = std::make_unique<Planet>(transform, 1.0e24f, 100.0f);
	auto planet2 = std::make_unique<Planet>(transform, 2.0e24f, 200.0f);

	simulation->spawnEntity(std::move(sun));
	simulation->spawnEntity(std::move(planet1));
	simulation->spawnEntity(std::move(planet2));

	EXPECT_NE(simulation->getSun(), nullptr);
	EXPECT_EQ(simulation->getPlanets().size(), 2);

	const auto& planets = simulation->getPlanets();
	EXPECT_EQ(planets[0]->getMass(), 1.0e24f);
	EXPECT_EQ(planets[1]->getMass(), 2.0e24f);
}
