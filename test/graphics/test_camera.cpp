#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "graphics/camera.hpp"

using namespace solarsim;

class CameraTest : public ::testing::Test {
	protected:
		void SetUp() override {
			CameraConfig config;
			config.Yaw = -90.0f;
			config.Pitch = 0.0f;
			config.Fov = 45.0f;
			config.RenderDistance = 100.0f;
			config.Speed = 2.5f;
			config.Sensitivity = 0.1f;

			camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 0.0f), config);
		}

		std::unique_ptr<Camera> camera;
};

// Test 1: Camera construction and basic properties
TEST_F(CameraTest, Initialization) {
	EXPECT_EQ(camera->getPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(camera->getWorldUp(), glm::vec3(0.0f, 1.0f, 0.0f));

	EXPECT_NEAR(camera->getFront().x, 0.0f, 0.001f);
	EXPECT_NEAR(camera->getFront().y, 0.0f, 0.001f);
	EXPECT_NEAR(camera->getFront().z, -1.0f, 0.001f);
}

// Test 2: View matrix getter
TEST_F(CameraTest, ViewMatrix) {
	auto viewMatrix = camera->getViewMatrix();

	auto invView = glm::inverse(viewMatrix);
	auto identity = viewMatrix * invView;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				EXPECT_NEAR(identity[i][j], 1.0f, 0.001f);
			} else {
				EXPECT_NEAR(identity[i][j], 0.0f, 0.001f);
			}
		}
	}
}

// Test 3: Projection matrix getter
TEST_F(CameraTest, ProjectionMatrix) {
	auto projMatrix = camera->getProjectionMatrix();

	auto invProj = glm::inverse(projMatrix);
	auto identity = projMatrix * invProj;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				EXPECT_NEAR(identity[i][j], 1.0f, 0.001f);
			} else {
				EXPECT_NEAR(identity[i][j], 0.0f, 0.001f);
			}
		}
	}
}

// Test 4: Keyboard input callbacks
TEST_F(CameraTest, KeyboardMovement) {
	glm::vec3 initialPosition = camera->getPosition();

	camera->ProcessKeyboard(FORWARD, 1.0f);
	EXPECT_NE(camera->getPosition(), initialPosition);

	camera->ProcessKeyboard(BACKWARD, 1.0f);
	EXPECT_EQ(camera->getPosition(), initialPosition);
}

// Test 5: Mouse input callback
TEST_F(CameraTest, MouseMovement) {
	glm::vec3 initialFront = camera->getFront();

	camera->ProcessMouseMovement(10.0f, 0.0f);
	EXPECT_NE(camera->getFront(), initialFront);

	camera->ProcessMouseMovement(0.0f, 100.0f);
	EXPECT_NEAR(camera->getFront().y, sin(glm::radians(10.0f)), 0.001f);
}

// Test 6: Mouse scroll callback
TEST_F(CameraTest, MouseScroll) {
	CameraConfig config;
	config.Fov = 45.0f;
	Camera testCamera(glm::vec3(0.0f), config);

	testCamera.ProcessMouseScroll(5.0f);
	EXPECT_LT(testCamera.getFov(), 45.0f);

	testCamera.ProcessMouseScroll(-10.0f);
	EXPECT_GT(testCamera.getFov(), 40.0f);

	testCamera.ProcessMouseScroll(100.0f);
	EXPECT_GE(testCamera.getFov(), 1.0f);

	testCamera.ProcessMouseScroll(-100.0f);
	EXPECT_LE(testCamera.getFov(), 45.0f);
}
