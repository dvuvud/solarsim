#pragma once

#include <glad/glad.h>
#include <vector>

namespace solarsim {
	
	/**
	 * @brief Represents 3D geometry with OpenGL buffers
	 * 
	 * @note Handles both vertex array and buffer object management
	 * @warning Call setupBuffers() before rendering to initialize OpenGL state
	 */
	struct Mesh {
		/** Vertex array object handle */
		uint32_t vao = 0;
		/** Vertex buffer object handle */
		uint32_t vbo = 0;
		/** Element buffer object handle */
		uint32_t ebo = 0;
		/** Number of vertices in the mesh */
		uint32_t vertexCount = 0;

		/** OpenGL primitive type for the type of geometry to draw */
		GLenum drawMode = GL_TRIANGLES;
		/** Whether to use index buffer */
		bool useElements = false;

		/** Whether vertices include normals */
		bool useNormals = true;

		/** Raw vertex data */
		std::vector<float> vertices;
		/** Vertex indicdes for indexed rendering */
		std::vector<uint32_t> indices;

		/**
		 * @brief Initialize OpenGL buffers and vertex attributes
		 * 
		 * @note Creates VAO, VBO, and optionally EBO
		 * @warning Must be called with active OpenGL context
		 */
		void setupBuffers() {
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			if (useElements && !indices.empty()) {
				glGenBuffers(1, &ebo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
			}

			size_t fields = useNormals ? 2 : 1;
			size_t stride = fields * 3;

			// TODO: Add more vertex data
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);

			if (useNormals) {
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
			}

			glBindVertexArray(0);
		}
	};
}
