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
		float Speed = 10.f;
		float Sensitivity = 0.1f;
		float Fov = 45.0f;
		float RenderDistance = 200.f;
	};

	class Camera {
		public:
			Camera(glm::vec3 p_position, const CameraConfig& p_config = {});

			glm::mat4 getViewMatrix() const;
			glm::mat4 getProjectionMatrix() const;
			glm::vec3 getPosition() const { return Position; }
			float getYaw() const { return m_yaw; }
			float getPitch() const { return m_pitch; }
			float getFov() const { return m_fov; }
			float getRenderDistance() const { return m_renderDistance; }
			float getMovementSpeed() const { return m_movementSpeed; }
			float getMouseSensitivity() const { return m_mouseSensitivity; }
			void ProcessKeyboard(Camera_Movement direction, float deltaTime);
			void ProcessMouseMovement(float xoffset, float yoffset);
			void ProcessMouseScroll(float yoffset);
		private:
			void updateCameraVectors();

			glm::vec3 Position;
			glm::vec3 Front, Up, Right, WorldUp;

			float m_yaw;
			float m_pitch;
			float m_fov;
			float m_renderDistance;

			float m_movementSpeed;
			float m_mouseSensitivity;
	};
}
