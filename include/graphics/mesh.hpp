#pragma once

#include <glad/glad.h>
#include <vector>

namespace solarsim {
	struct Mesh {
		unsigned int vao;
		unsigned int vbo = 0;
		unsigned int ebo = 0;
		unsigned int vertexCount;

		GLenum drawMode = GL_TRIANGLES;
		bool useElements = false;

		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		void setupBuffers() {
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			if (useElements && !indices.empty()) {
				glGenBuffers(1, &ebo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
			}

			// TODO: Add more vertex data
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

			glBindVertexArray(0);
		}
	};
}
