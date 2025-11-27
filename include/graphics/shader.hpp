#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <string>

namespace solarsim {

	/**
	 * @brief Manages OpenGL shader program compilation and uniform setting
	 * 
	 * @note Automatically binds common uniform blocks (Camera, Lights, Rigidbody)
	 * @warning Shader sources must be valid GLSL code
	 */
	struct Shader
	{
		/** The OpenGL shader program handle */
		uint32_t programID = 0;

		/**
		 * @brief Activate this shader for rendering
		 */
		void use() {
			glUseProgram(programID);
		}

		/**
		 * @brief Bind uniform buffer blocks to predefined binding points
		 * 
		 * @note Binds CameraBuffer(0), LightsBuffer(1), RigidbodyBuffer(2)
		 * @warning Call this after compilation, it's called automatically by compile()
		 */
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

		// Uniform setting methods

		/**
		 * @brief Set a mat4 uniform value
		 * @param name Uniform variable name in shader
		 * @param value 4x4 matrix value
		 */
		void setUniform(const std::string& name, const glm::mat4& value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
			}
		}
		/**
		 * @brief Set a vec3 uniform value
		 * @param name Uniform variable name in shader
		 * @param value 3-component vector value
		 */
		void setUniform(const std::string& name, const glm::vec3& value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform3fv(loc, 1, glm::value_ptr(value));
			}
		}
		/**
		 * @brief Set a float uniform value
		 * @param name Uniform variable name in shader
		 * @param value Single float value
		 */
		void setUniform(const std::string& name, float value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1f(loc, value);
			}
		}
		/**
		 * @brief Set an integer uniform value
		 * @param name Uniform variable name in shader
		 * @param value Integer value
		 */
		void setUniform(const std::string& name, int value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1i(loc, value);
			}
		}
		/**
		 * @brief Set a boolean uniform value
		 * @param name Uniform variable name in shader
		 * @param value Boolean value (converted to 0 or 1)
		 */
		void setUniform(const std::string& name, bool value) {
			int loc = glGetUniformLocation(programID, name.c_str());
			if (loc != -1) {
				glUniform1i(loc, value);
			}
		}

		/**
		 * @brief Compile and link shader program from source code
		 * @param vertexSrc Vertex shader source code
		 * @param fragmentSrc Fragment shader source code
		 * 
		 * @note Automatically calls bindBlocks() after successful compilation
		 */
		void compile(const std::string& vertexSrc, const std::string& fragmentSrc) {
			uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
			const char* vSrc = vertexSrc.c_str();
			glShaderSource(vertex, 1, &vSrc, nullptr);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");

			uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
			const char* fSrc = fragmentSrc.c_str();
			glShaderSource(fragment, 1, &fSrc, nullptr);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");

			uint32_t program = glCreateProgram();
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

		/**
		 * @brief Check for shader compilation or linking errors
		 * @param shader Shader or program object to check
		 * @param type Type of shader ("VERTEX", "FRAGMENT", or "PROGRAM")
		 * 
		 * @note Prints errors to std::cerr
		 */
		void checkCompileErrors(uint32_t shader, const std::string& type) {
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
