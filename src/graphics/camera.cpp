#include <graphics/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace solarsim {
	Camera::Camera(glm::vec3 p_position, const CameraConfig& p_config)
		: Position(p_position),
		WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
		m_yaw(p_config.Yaw),
		m_pitch(p_config.Pitch), 
		m_fov(p_config.Fov),
		m_renderDistance(p_config.RenderDistance),
		m_movementSpeed(p_config.Speed),
		m_mouseSensitivity(p_config.Sensitivity)
		{
			updateCameraVectors();
		}

	glm::mat4 Camera::getViewMatrix() const
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		// TODO: 800.f / 600.f should be replaced by m_aspectRation or similar
		return glm::perspective(glm::radians(m_fov), 800.f / 600.f, 0.1f, m_renderDistance);
	}

	void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = m_movementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
		if (direction == UP)
			Position += WorldUp * velocity;
		if (direction == DOWN)
			Position -= WorldUp * velocity;
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= m_mouseSensitivity;
		yoffset *= m_mouseSensitivity;

		m_yaw += xoffset;
		m_pitch += yoffset;

		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;

		updateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float yoffset)
	{
		m_fov -= (float)yoffset;
		if (m_fov < 1.0f)
			m_fov = 1.0f;
		if (m_fov > 45.0f)
			m_fov = 45.0f;
	}

	void Camera::updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
}
