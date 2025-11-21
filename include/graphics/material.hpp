#pragma once

#include <graphics/shader.hpp>
#include <string>

namespace solarsim {
	class Material {
		private:
			std::shared_ptr<Shader> m_shader;
			glm::vec3 ambient, specular, diffuse;
			float shininess;
		public:
			Material() = default;
			Material(const glm::vec3& amb = glm::vec3(1.0f), const glm::vec3& spec = glm::vec3(1.0f),
					const glm::vec3& diffuse = glm::vec3(1.0f), float shininess = 1.0f) 
				: ambient(amb), specular(spec), diffuse(diffuse), shininess(shininess) {}
			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;

			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;

			virtual ~Material() = default;

			const Shader* getShader() const { return m_shader.get(); }
			void apply() const {
				m_shader->setVec3("uMaterial.ambient", ambient);
				m_shader->setVec3("uMaterial.diffuse", diffuse);
				m_shader->setVec3("uMaterial.specular", specular);
				m_shader->setFloat("uMaterial.shininess", shininess);
			}
	};
}
