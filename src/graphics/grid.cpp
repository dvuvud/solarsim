#include <graphics/grid.hpp>
#include <simulation/simulation.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Grid::Grid(size_t p_size, float p_spacing) : m_shader("assets/shaders/grid.vert", "assets/shaders/grid.frag"),
	m_VAO(0), m_VBO(0), m_EBO(0), m_size(p_size), m_spacing(p_spacing) {
		generateGrid();
		setupBuffer();
		m_originalVertices = m_vertices;
	}

	Grid::~Grid() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

	void Grid::generateGrid() {
		m_vertices.clear();
		m_indices.clear();

		// Create individual points at each vertex in the grid
		for (int z = -m_size; z < m_size; ++z) {
			for (int x = -m_size; x < m_size; ++x) {
				float xPos = x * m_spacing;
				float zPos = z * m_spacing;
				m_vertices.insert(m_vertices.end(), {xPos, 0.f, zPos});
			}
		}

		int pointsPerSide = m_size * 2;

		// Link those points together 2x2 to create horizontal lines
		for (GLuint z = 0; z < pointsPerSide; ++z) {
			for (GLuint x = 0; x < pointsPerSide - 1; ++x) {
				GLuint start = z * pointsPerSide + x;
				GLuint end = start + 1;
				m_indices.insert(m_indices.end(), {start, end});
			}
		}

		// Link those points together 2x2 to create vertical lines
		for (GLuint x = 0; x < pointsPerSide; ++x) {
			for (GLuint z = 0; z < pointsPerSide - 1; ++z) {
				GLuint start = z * pointsPerSide + x;
				GLuint end = start + pointsPerSide;
				m_indices.insert(m_indices.end(), {start, end});
			}
		}
	}

	void Grid::setupBuffer() {
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}

	void Grid::draw() const {
		glBindVertexArray(m_VAO);
		glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}
