#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
	public:
		// the program ID
		unsigned int ID;

		// constructor reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);
		// use/activate the shader
		void bind();
		// utility uniform functions
		void setBool(const std::string &name, bool value) const;  
		void setInt(const std::string &name, int value) const;   
		void setFloat(const std::string &name, float value) const;
		void setMat4(const std::string &name, const glm::mat4& value) const;
		void setVec3(const std::string &name, const glm::vec3& value) const;
};
