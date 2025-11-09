#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../graphics/shader.hpp"

#include "material.hpp"
#include "mesh.hpp"

struct Transform {
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 getModelMatrix() const {
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));  
		model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);
		return model;
	}
};

class Entity {
	public:
		Entity(const std::string& name = "Entity") : name(name) {}
		virtual ~Entity() = default;

		virtual void render(Shader& shader) = 0;

		virtual void update(float deltaTime) {}

		Transform& getTransform() { return transform; }
		const Transform& getTransform() const { return transform; }

		void setMaterial(const std::shared_ptr<Material> material) { this->material = material; }
		std::shared_ptr<Material> getMaterial() const { return material; }

		void setMesh(const std::shared_ptr<Mesh> mesh) { this->mesh = mesh; }
		std::shared_ptr<Mesh> getMesh() const { return mesh; }

		void setPosition(const glm::vec3& position) { transform.position = position; }
		glm::vec3 getPosition() const { return transform.position; }

		void setRotation(const glm::vec3& rotation) { transform.rotation = rotation; }
		glm::vec3 getRotation() const { return transform.rotation; }

		void setScale(const glm::vec3& scale) { transform.scale = scale; }
		glm::vec3 getScale() const { return transform.scale; }

	protected:
		Transform transform;
		std::string name;
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Material> material;
};

