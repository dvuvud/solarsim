#include <mesh/cube.hpp>

namespace solarsim {
	Cube::Cube() {
		m_vertices = std::vector<Vertex> {
			{ {-0.5,-0.5,-0.5}, {0,0,0}, {0,0} }, // v0
			{ { 0.5,-0.5,-0.5}, {0,0,0}, {1,0} }, // v1
			{ { 0.5, 0.5,-0.5}, {0,0,0}, {1,1} }, // v2
			{ {-0.5, 0.5,-0.5}, {0,0,0}, {0,1} }, // v3
			{ {-0.5,-0.5, 0.5}, {0,0,0}, {0,0} }, // v4
			{ { 0.5,-0.5, 0.5}, {0,0,0}, {1,0} }, // v5
			{ { 0.5, 0.5, 0.5}, {0,0,0}, {1,1} }, // v6
			{ {-0.5, 0.5, 0.5}, {0,0,0}, {0,1} }, // v7
		};
		m_indices = std::vector<unsigned int> {
			// Front face: uses v0, v1, v2, v3
			0, 1, 2,   // first triangle
			2, 3, 0,   // second triangle

			// Back face (uses vertices 4,5,6,7)  
			5, 4, 7,   // first triangle
			7, 6, 5,   // second triangle

			// Left face (uses vertices 4,0,3,7)
			4, 0, 3,   // first triangle
			3, 7, 4,   // second triangle

			// Right face (uses vertices 1,5,6,2)
			1, 5, 6,   // first triangle  
			6, 2, 1,   // second triangle

			// Bottom face (uses vertices 4,5,1,0)
			4, 5, 1,   // first triangle
			1, 0, 4,   // second triangle

			// Top face (uses vertices 3,2,6,7)
			3, 2, 6,   // first triangle
			6, 7, 3,   // second triangle
		};
		setupMesh();
	}
}
