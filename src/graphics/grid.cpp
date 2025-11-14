#include <graphics/grid.hpp>
#include <simulation/simulation.hpp>

namespace solarsim {
	Grid::Grid(size_t p_size, float p_spacing) : m_shader("assets/shaders/grid.vert", "assets/shaders/grid.frag"),
	m_VAO(0), m_VBO(0), m_size(p_size), m_spacing(p_spacing) {
		generateGrid();
		setupBuffer();
	}

	Grid::~Grid() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

	void Grid::update(const Simulation& p_sim) {
	}

	void Grid::generateGrid() {
		float extent = m_size * m_spacing;

		for (int z = -m_size; z <= m_size; ++z) {
			float zPos = z * m_spacing;
			m_vertices.insert(m_vertices.end(), {
					-extent, 0.f, zPos,
					extent, 0.f, zPos
					});
		}

		for (int x = -m_size; x <= m_size; ++x) {
			float xPos = x * m_spacing;
			m_vertices.insert(m_vertices.end(), {
					xPos, 0.f, -extent,
					xPos, 0.f, extent
					});
		}
	}

	void Grid::setupBuffer() {
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	}

	void Grid::draw(const glm::mat4& uVP) const {
		m_shader.bind();
		m_shader.setMat4("uVP", uVP);
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_LINES, 0, m_vertices.size() / 3);
	}
}
