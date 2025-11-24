#include <gtest/gtest.h>
#include <components/transform_component.hpp>

using namespace solarsim;

class TransformComponentTest : public ::testing::Test {
	protected:
		void SetUp() override {
			transform = std::make_unique<TransformComponent>();
		}

		void TearDown() override {
			transform.reset();
		}

		std::unique_ptr<TransformComponent> transform;
};

// Test 1: Default values
TEST_F(TransformComponentTest, DefaultValues) {
	EXPECT_EQ(transform->position, glm::vec3(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(transform->rotation, glm::quat(1.0f, 0.0f, 0.0f, 0.0f));
	EXPECT_EQ(transform->scale, glm::vec3(1.0f, 1.0f, 1.0f));
	EXPECT_TRUE(transform->dirty);
}

// Test 2: Model matrix calculation
TEST_F(TransformComponentTest, ModelMatrixCalculation) {
	transform->position = glm::vec3(2.0f, 3.0f, 4.0f);
	transform->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform->dirty = true;

	glm::mat4 model = transform->getModelMatrix();

	glm::mat4 expected = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 3.0f, 4.0f));

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_NEAR(model[i][j], expected[i][j], 0.001f);
		}
	}

	// Should not be dirty after calculation
	EXPECT_FALSE(transform->dirty);
}

// Test 3: Caching behavior
TEST_F(TransformComponentTest, ModelMatrixCaching) {
	transform->position = glm::vec3(1.0f, 0.0f, 0.0f);
	transform->dirty = true;

	glm::mat4 firstCall = transform->getModelMatrix();
	glm::mat4 secondCall = transform->getModelMatrix();

	// Should return same matrix without recalculating
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			EXPECT_EQ(firstCall[i][j], secondCall[i][j]);
		}
	}
}

// Test 4: Rotation with quaternions
TEST_F(TransformComponentTest, RotationQuaternions) {
	transform->rotation = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	transform->dirty = true;

	glm::mat4 model = transform->getModelMatrix();

	// Should create a proper rotation matrix
	EXPECT_NEAR(model[0][0], 0.0f, 0.001f);
	EXPECT_NEAR(model[0][2], -1.0f, 0.001f);
	EXPECT_NEAR(model[2][0], 1.0f, 0.001f);
	EXPECT_NEAR(model[2][2], 0.0f, 0.001f);
}
