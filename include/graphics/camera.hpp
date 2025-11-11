#pragma once

#include <glm/glm.hpp>

namespace solarsim {

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
			Camera(glm::vec3 position, const CameraConfig& config = {})
				: Position(position),
				WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
				Yaw(config.Yaw),
				Pitch(config.Pitch), 
				Fov(config.Fov),
				RenderDistance(config.RenderDistance),
				MovementSpeed(config.Speed),
				MouseSensitivity(config.Sensitivity)
				{ updateCameraVectors(); }

			glm::mat4 GetViewMatrix() const;
			glm::mat4 GetProjectionMatrix() const;
			void ProcessKeyboard(Camera_Movement direction, float deltaTime);
			void ProcessMouseMovement(float xoffset, float yoffset);
			void ProcessMouseScroll(float yoffset);
		private:
			void updateCameraVectors();

			glm::vec3 Position;
			glm::vec3 Front, Up, Right, WorldUp;

			float Yaw;
			float Pitch;
			float Fov;
			float RenderDistance;

			float MovementSpeed;
			float MouseSensitivity;
	};
}
