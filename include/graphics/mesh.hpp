#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices = {});
		~Mesh();
		void render() const;
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		GLuint VAO, VBO, EBO;

		void setupMesh();
};
