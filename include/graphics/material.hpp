#pragma once

#include <graphics/shader.hpp>
#include <string>

namespace solarsim {
	class Material {
		private:
			Shader m_shader;
			glm::vec3 ambient, specular, diffuse;
			float shininess;
		public:
			Material() = default;
			Material(const std::string& vertexPath, const std::string& fragPath,
					const glm::vec3& amb = glm::vec3(1.0f), const glm::vec3& spec = glm::vec3(1.0f),
					const glm::vec3& diffuse = glm::vec3(1.0f), float shininess = 1.0f) 
				: m_shader(vertexPath.c_str(), fragPath.c_str()), ambient(amb),
				specular(spec), diffuse(diffuse), shininess(shininess) {}
			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;

			// TODO: Update this later as Material gets more things added to it
			Material(Material&&) noexcept = default;
			Material& operator=(Material&&) noexcept = default;

			virtual ~Material() = default;

			const Shader* getShader() const { return &m_shader; }
			void apply() const {
				m_shader.setVec3("uMaterial.ambient", ambient);
				m_shader.setVec3("uMaterial.diffuse", diffuse);
				m_shader.setVec3("uMaterial.specular", specular);
				m_shader.setFloat("uMaterial.shininess", shininess);
			}
	};
}
