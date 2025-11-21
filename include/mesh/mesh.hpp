#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace solarsim {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoords;
	};

	class Mesh {
		public:
			Mesh() = default;
			Mesh(const std::vector<Vertex>& p_vertices, const std::vector<unsigned int>& p_indices = {});
			Mesh(const Mesh&) = delete;
			Mesh& operator=(const Mesh&) = delete;
			Mesh(Mesh&& other) noexcept;
			Mesh& operator=(Mesh&& other) noexcept;
			~Mesh();
			void draw() const;
		protected:
			std::vector<Vertex> m_vertices;
			std::vector<unsigned int> m_indices;

			GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;

			void setupMesh();
	};
}
