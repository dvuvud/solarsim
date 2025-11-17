#include <glad/glad.h>
#include <mesh/mesh.hpp>

namespace solarsim {
	Mesh::Mesh(const std::vector<Vertex>& p_vertices, const std::vector<unsigned int>& p_indices)
		: m_vertices(p_vertices), m_indices(p_indices)
	{
		setupMesh();
	}

	Mesh::Mesh(Mesh&& other) noexcept
		: m_vertices(std::move(other.m_vertices)),
		  m_indices(std::move(other.m_indices)),
		  m_VAO(other.m_VAO),
		  m_VBO(other.m_VBO),
		  m_EBO(other.m_EBO)
	{
		other.m_VAO = 0;
		other.m_VBO = 0;
		other.m_EBO = 0;
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept {
		if (this != &other) {
			// free existing GL resources owned by this
			if (m_VAO != 0) glDeleteVertexArrays(1, &m_VAO);
			if (m_VBO != 0) glDeleteBuffers(1, &m_VBO);
			if (m_EBO != 0) glDeleteBuffers(1, &m_EBO);

			m_vertices = std::move(other.m_vertices);
			m_indices = std::move(other.m_indices);
			m_VAO = other.m_VAO;
			m_VBO = other.m_VBO;
			m_EBO = other.m_EBO;

			other.m_VAO = 0;
			other.m_VBO = 0;
			other.m_EBO = 0;
		}
		return *this;
	}

	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		if (m_EBO != 0) {
			glDeleteBuffers(1, &m_EBO);
		}
	}

	void Mesh::render() const {
		glBindVertexArray(m_VAO);
		if (m_indices.empty()) {
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size());
		} else {
			glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);
	}

	void Mesh::setupMesh() {
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
				(void*)offsetof(Vertex, normal));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
				(void*)offsetof(Vertex, texCoords));

		if (!m_indices.empty()) {
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
					m_indices.data(), GL_STATIC_DRAW);
		}
	}
}
