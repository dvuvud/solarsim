#pragma once

#include <mesh/mesh.hpp>
#include <graphics/material.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace solarsim {
	class Shader;
	class Camera;
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
			Entity(const Transform& p_transform, Mesh p_mesh, const Material& p_material, float m, float r)
				: m_transform(p_transform), m_mesh(std::move(p_mesh)), m_material(p_material), m_mass(m), m_radius(r), m_velocity(glm::vec3(0.f)) {}
			virtual ~Entity() = default;

			virtual void update(float deltaTime) {
				glm::vec3 acceleration = m_accumulatedForce / m_mass;

				m_velocity += acceleration * deltaTime;
				m_transform.position += m_velocity * deltaTime;

				m_accumulatedForce = glm::vec3(0.0f);
			}

			virtual void applyForce(const glm::vec3& force) {
				m_accumulatedForce += force;
			}

			void setTransform(const Transform& p_transform) { m_transform = p_transform; }
			Transform& getTransform() { return m_transform; }
			const Transform& getTransform() const { return m_transform; }

			const Material& getMaterial() const { return m_material; }

			const Mesh& getMesh() const { return m_mesh; }

			void setVelocity(const glm::vec3& p_velocity) { m_velocity = p_velocity; }
			const glm::vec3& getVelocity() { return m_velocity; }

			void setPosition(const glm::vec3& p_position) { m_transform.position = p_position; }
			glm::vec3 getPosition() const { return m_transform.position; }

			void setRotation(const glm::vec3& p_rotation) { m_transform.rotation = p_rotation; }
			glm::vec3 getRotation() const { return m_transform.rotation; }

			void setScale(const glm::vec3& p_scale) { m_transform.scale = p_scale; }
			glm::vec3 getScale() const { return m_transform.scale; }

			float getMass() const { return m_mass; }
			float getRadius() const { return m_radius; }
		protected:
			Transform m_transform;
			glm::vec3 m_velocity;
			glm::vec3 m_accumulatedForce;
			Mesh m_mesh;
			Material m_material;
			float m_mass;
			float m_radius;
	};
}
