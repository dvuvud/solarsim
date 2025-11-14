#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "shader.hpp"
#include <vector>

namespace solarsim {
	class Shader;
	class Simulation;
	class Grid {
		public:
			Grid(size_t p_size = 20, float p_spacing = 1.f);
			~Grid();
			void update(const Simulation& p_sim);
			void draw(const glm::mat4& uMVP) const;
		private:
			void generateGrid();
			void setupBuffer();
			int m_size;
			float m_spacing;
			Shader m_shader;
			std::vector<GLfloat> m_vertices;
			GLuint m_VBO, m_VAO;
	};
}
