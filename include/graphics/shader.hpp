#pragma once

#include <string>
#include <glm/glm.hpp>

namespace solarsim {
	class Shader
	{
		public:

			unsigned int m_ID;

			Shader(const char* p_vertexPath, const char* p_fragmentPath);
			
			void bind() const;

			// utility uniform functions
			void setBool(const std::string &name, bool value) const;  
			void setInt(const std::string &name, int value) const;   
			void setFloat(const std::string &name, float value) const;
			void setMat4(const std::string &name, const glm::mat4& value) const;
			void setVec3(const std::string &name, const glm::vec3& value) const;
	};
}
