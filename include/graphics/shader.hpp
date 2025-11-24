#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

namespace solarsim {
	struct Shader
	{
		unsigned int programID = 0;

		void use() {
			glUseProgram(programID);
		}

		void bindBlocks() {
			int loc = glGetUniformBlockIndex(programID, "CameraBuffer"); 
			if (loc != GL_INVALID_INDEX) {
				glUniformBlockBinding(programID, loc, 0);
			}
			loc = glGetUniformBlockIndex(programID, "LightsBuffer"); 
			if (loc != GL_INVALID_INDEX) {
				glUniformBlockBinding(programID, loc, 1);
			}
			loc = glGetUniformBlockIndex(programID, "RigidbodyBuffer"); 
			if (loc != GL_INVALID_INDEX) {
				glUniformBlockBinding(programID, loc, 2);
			}
		}

		void setUniform(const std::string& name, const glm::mat4& value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
			}
		}
		void setUniform(const std::string& name, const glm::vec3& value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform3fv(loc, 1, glm::value_ptr(value));
			}
		}
		void setUniform(const std::string& name, float value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1f(loc, value);
			}
		}
		void setUniform(const std::string& name, int value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1i(loc, value);
			}
		}
		void setUniform(const std::string& name, bool value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1i(loc, value);
			}
		}

		void compile(const std::string& vertexSrc, const std::string& fragmentSrc) {
			unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
			const char* vSrc = vertexSrc.c_str();
			glShaderSource(vertex, 1, &vSrc, nullptr);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");

			unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
			const char* fSrc = fragmentSrc.c_str();
			glShaderSource(fragment, 1, &fSrc, nullptr);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");

			unsigned int program = glCreateProgram();
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			checkCompileErrors(program, "PROGRAM");

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			programID = program;

			// Bind blocks once
			bindBlocks();
		}

		void checkCompileErrors(unsigned int shader, const std::string& type) {
			int success;
			char infoLog[1024];
			if (type != "PROGRAM") {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
					std::cerr << "Shader Compilation Error (" << type << "): " << infoLog << "\n";
				}
			} else {
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
					std::cerr << "Shader Linking Error (" << type << "): " << infoLog << "\n";
				}
			}
		}

	};
}
