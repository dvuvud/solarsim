#pragma once

#include <glm/glm.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct CameraConfig {
	float Yaw = -90.0f;
	float Pitch = 0.0f;
	float Speed = 2.5f;
	float Sensitivity = 0.1f;
	float Fov = 45.0f;
	float RenderDistance = 100.f;
};

class Camera {
	public:
		glm::vec3 Position;
		glm::vec3 Front, Up, Right, WorldUp;

		float Yaw;
		float Pitch;
		float Fov;
		float RenderDistance;

		float MovementSpeed;
		float MouseSensitivity;

		Camera(glm::vec3 position = glm::vec3(0.0f), const CameraConfig& config = {});
		glm::mat4 GetViewMatrix();
		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset);
		void ProcessMouseScroll(float yoffset);
	private:
		void updateCameraVectors();
};
