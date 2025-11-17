#pragma once

#include <string>
#include <glm/glm.hpp>

namespace solarsim {
	class Shader
	{
		public:

			unsigned int m_ID;

			Shader() = default;
			Shader(const char* p_vertexPath, const char* p_fragmentPath);

			~Shader();

			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;

			Shader(Shader&& other) noexcept;
			Shader& operator=(Shader&& other) noexcept;

			void bind() const;

			// utility uniform functions
			void setBool(const std::string &name, bool value) const;  
			void setInt(const std::string &name, int value) const;   
			void setFloat(const std::string &name, float value) const;
			void setMat4(const std::string &name, const glm::mat4& value) const;
			void setVec3(const std::string &name, const glm::vec3& value) const;
			void setVec4(const std::string &name, const glm::vec4& value) const;
			void setVec4Array(const std::string &name, const std::vector<glm::vec4>& value) const;
			void setVec3Array(const std::string &name, const std::vector<glm::vec3>& value) const;
			void setFloatArray(const std::string &name, const std::vector<float>& value) const;
	};
}
