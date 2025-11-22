#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <string>

namespace solarsim {
	struct Shader
	{
		unsigned int programID;
		void use() {
			glUseProgram(programID);
		}
		void setUniform(const std::string& name, const glm::mat4& value) {
			glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
	};
}
