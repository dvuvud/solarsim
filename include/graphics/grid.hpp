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
			Grid(size_t p_size = 50, float p_spacing = 10.f);
			~Grid();
			void draw() const;
			const Shader* getShader() const { return &m_shader; }
		private:
			void generateGrid();
			void setupBuffer();
			int m_size;
			float m_spacing;
			Shader m_shader;
			std::vector<GLfloat> m_originalVertices;
			std::vector<GLfloat> m_vertices;
			std::vector<GLuint> m_indices;
			GLuint m_VBO, m_VAO, m_EBO;
	};
}
