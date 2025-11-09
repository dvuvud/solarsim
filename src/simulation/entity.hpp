#pragma once

#include <string>
#include <glm/glm.hpp>

#include "../graphics/shader.hpp"

class Entity {
protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::string name;
	bool isActive = true;

public:
	Entity(const std::string& name = "Entity") : name(name) {}
	virtual ~Entity() = default;

	virtual void render(Shader& shader) = 0;

	virtual void update(float deltaTime) {}

	// Getters/setters for common properties
	void setPosition(const glm::vec3& position) { this->position = position; }
	glm::vec3 getPosition() const { return position; }
	void setActive(bool active) { isActive = active; }
	bool getActive() const { return isActive; }
};

