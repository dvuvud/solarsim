#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace solarsim {
	class Mesh;
	class Material;
	class Shader;
	struct Transform {
		glm::vec3 position = glm::vec3(0.f,0.f,0.f);
		glm::vec3 rotation = glm::vec3(0.f,0.f,0.f);
		glm::vec3 scale = glm::vec3(1.f,1.f,1.f);

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
			Entity(const Transform& transform, Mesh* mesh, Material* material)
				: transform(transform), mesh(mesh), material(material) {}
			virtual ~Entity() = default;

			virtual void render(Shader& shader) = 0;

			virtual void update(float deltaTime) = 0;

			void setTransform(const Transform& transform) { this->transform = transform; }
			Transform& getTransform() { return transform; }
			const Transform& getTransform() const { return transform; }

			void setMaterial(Material* material) { this->material = material; }
			Material* getMaterial() const { return material; }

			void setMesh(Mesh* mesh) { this->mesh = mesh; }
			Mesh* getMesh() const { return mesh; }

			void setPosition(const glm::vec3& position) { transform.position = position; }
			glm::vec3 getPosition() const { return transform.position; }

			void setRotation(const glm::vec3& rotation) { transform.rotation = rotation; }
			glm::vec3 getRotation() const { return transform.rotation; }

			void setScale(const glm::vec3& scale) { transform.scale = scale; }
			glm::vec3 getScale() const { return transform.scale; }
		protected:
			Transform transform;
			Mesh* mesh;
			Material* material;
	};
}
