#include <graphics/shader.hpp>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace solarsim {
	Shader::Shader(const char* p_vertexPath, const char* p_fragmentPath) {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		try 
		{
			// open files
			vShaderFile.open(p_vertexPath);
			fShaderFile.open(p_fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();		
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode   = vShaderStream.str();
			fragmentCode = fShaderStream.str();		
		}
		catch(std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		// shader Program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if(!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}


		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	Shader::Shader(Shader&& other) noexcept
		: m_ID(other.m_ID)
		{
			other.m_ID = 0;
		}

	Shader& Shader::operator=(Shader&& other) noexcept {
		if (this != &other) {
			if (m_ID != 0) {
				glDeleteProgram(m_ID);
			}
			m_ID = other.m_ID;
			other.m_ID = 0;
		}
		return *this;
	}

	Shader::~Shader() {
		if (m_ID != 0) {
			glDeleteProgram(m_ID);
			m_ID = 0;
		}
	}

	void Shader::bind() const {
		glUseProgram(m_ID);
	}

	void Shader::setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void Shader::setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::setVec3(const std::string &name, const glm::vec3& value) const {
		glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setVec4(const std::string &name, const glm::vec4& value) const {
		glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
	}

	void Shader::setVec4Array(const std::string &name, const std::vector<glm::vec4>& value) const {
		glUniform4fv(glGetUniformLocation(m_ID, name.c_str()), (GLsizei)value.size(), (const GLfloat*)value.data());
	}

	void Shader::setVec3Array(const std::string &name, const std::vector<glm::vec3>& value) const {
		glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), (GLsizei)value.size(), (const GLfloat*)value.data());
	}

	void Shader::setFloatArray(const std::string &name, const std::vector<float>& value) const {
		glUniform1fv(glGetUniformLocation(m_ID, name.c_str()), (GLsizei)value.size(), value.data());
	}
}
