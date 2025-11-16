#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "shader.hpp"
#include <vector>
#include <memory>

namespace solarsim {
	class Shader;
	class Simulation;
	class Entity;
	class Grid {
		public:
			Grid(GLint p_size = 100, GLfloat p_spacing = 3.5f);
			~Grid();
			void draw() const;
			const Shader* getShader() const { return &m_shader; }
		private:
			void generateGrid();
			void setupBuffer();
			GLint m_size;
			GLfloat m_spacing;
			Shader m_shader;
			std::vector<GLfloat> m_originalVertices;
			std::vector<GLfloat> m_vertices;
			std::vector<GLuint> m_indices;
			GLuint m_VBO, m_VAO, m_EBO;
	};
}
