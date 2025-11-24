#include <managers/asset_manager.hpp>

#include <graphics/mesh.hpp>
#include <graphics/material.hpp>
#include <graphics/shader.hpp>

#include <fstream>
#include <istream>

namespace solarsim {
	AssetManager& AssetManager::get() {
		static AssetManager instance;
		return instance;
	}

	std::shared_ptr<Mesh> AssetManager::LoadMesh(const std::string& meshID) {
		auto it = loadedMeshes.find(meshID);
		if (it != loadedMeshes.end()) return it->second;

		// TODO: Implement assimp and replace the following with model loading
		auto mesh = std::make_shared<Mesh>();
		if (meshID == "cube") {
			mesh->vertices = cube;
			mesh->vertexCount = 36;
		} else if (meshID == "sphere") {
			mesh->useElements = true;

			generateSphere(mesh->vertices, mesh->indices);

			mesh->vertexCount = mesh->indices.size();
		} else if (meshID == "grid") {
			mesh->useElements = true;
			mesh->drawMode = GL_LINES;
			mesh->useNormals = false;

			generateGrid(mesh->vertices, mesh->indices);

			mesh->vertexCount = mesh->indices.size();
		}

		mesh->setupBuffers();
		loadedMeshes[meshID] = mesh;
		return mesh;
	}
	std::shared_ptr<Material> AssetManager::LoadMaterial(const std::string& materialID) {
		auto it = loadedMaterials.find(materialID);
		if (it != loadedMaterials.end()) return it->second;

		// TODO: Add actual functionality for loading materials
		auto material = std::make_shared<Material>();
		if (materialID == "mercury") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(0.5, 0.5, 0.5);
		} else if (materialID == "venus") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(1.0, 0.9, 0.6);
		} else if (materialID == "earth") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(0.2, 0.5, 1.0);
		} else if (materialID == "mars") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(1.0, 0.4, 0.2);
		} else if (materialID == "jupiter") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(0.9, 0.7, 0.5);
		} else if (materialID == "saturn") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(1.0, 0.9, 0.6);
		} else if (materialID == "uranus") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(0.5, 1.0, 1.0);
		} else if (materialID == "neptune") {
			material->shaderID = "simple";
			material->albedo=glm::vec3(0.3, 0.4, 1.0);
		} else if (materialID == "sun") {
			material->shaderID = "light";
		} else if (materialID == "grid") {
			material->shaderID = "grid";
		}
		loadedMaterials[materialID] = material;
		return material;
	}
	std::shared_ptr<Shader> AssetManager::LoadShader(const std::string& shaderID) {
		auto it = loadedShaders.find(shaderID);
		if (it != loadedShaders.end()) return it->second;

		std::string vertexPath = "assets/shaders/" + shaderID + ".vert";
		std::string fragmentPath = "assets/shaders/" + shaderID + ".frag";

		std::ifstream vFile(vertexPath), fFile(fragmentPath);
		if (!vFile || !fFile) {
			std::cerr << "Failed to open shader files for " << shaderID << "\n";
			return nullptr;
		}

		std::string vertexSrc((std::istreambuf_iterator<char>(vFile)), std::istreambuf_iterator<char>());
		std::string fragmentSrc((std::istreambuf_iterator<char>(fFile)), std::istreambuf_iterator<char>());

		auto shader = std::make_shared<Shader>();
		shader->compile(vertexSrc, fragmentSrc);
		loadedShaders[shaderID] = shader;
		return shader;
	}

	void AssetManager::generateSphere(std::vector<float>& vertices, std::vector<unsigned int>& indices, float radius, int resolution)
	{
		int latCount = resolution + 1;
		int lonCount = resolution + 1;

		vertices.clear();
		indices.clear();

		vertices.reserve((size_t)latCount * lonCount * 6); // 6 floats per vertex
		indices.reserve((size_t)resolution * resolution * 6); // 2 triangles per quad -> 6 indices

		// generate vertices (position + normal)
		for (int lat = 0; lat < latCount; ++lat) {
			float theta = (float)lat / (float)resolution * glm::pi<float>();
			float sinTheta = std::sin(theta);
			float cosTheta = std::cos(theta);

			for (int lon = 0; lon < lonCount; ++lon) {
				float phi = (float)lon / (float)resolution * 2.0f * glm::pi<float>();
				float sinPhi = std::sin(phi);
				float cosPhi = std::cos(phi);

				// normal
				float nx = cosPhi * sinTheta;
				float ny = cosTheta;
				float nz = sinPhi * sinTheta;

				// position = normal * radius
				float px = radius * nx;
				float py = radius * ny;
				float pz = radius * nz;

				vertices.push_back(px);
				vertices.push_back(py);
				vertices.push_back(pz);
				vertices.push_back(nx);
				vertices.push_back(ny);
				vertices.push_back(nz);
			}
		}

		// generate indices (two triangles per quad)
		for (int lat = 0; lat < resolution; ++lat) {
			for (int lon = 0; lon < resolution; ++lon) {
				unsigned int current = (unsigned int)(lat * lonCount + lon);
				unsigned int next = (unsigned int)((lat + 1) * lonCount + lon);

				// triangle 1
				indices.push_back(current);
				indices.push_back(next);
				indices.push_back(current + 1);

				// triangle 2
				indices.push_back(current + 1);
				indices.push_back(next);
				indices.push_back(next + 1);
			}
		}
	}

	void AssetManager::generateGrid(std::vector<float>& vertices, std::vector<unsigned int>& indices, float spacing, int extent) {
		// Create individual points at each vertex in the grid
		for (int z = -extent; z < extent; ++z) {
			for (int x = -extent; x < extent; ++x) {
				GLfloat xPos = x * spacing;
				GLfloat zPos = z * spacing;
				vertices.insert(vertices.end(), {xPos, 0.f, zPos});
			}
		}

		GLuint pointsPerSide = extent * 2;

		// Link those points together 2x2 to create horizontal lines
		for (GLuint z = 0; z < pointsPerSide; ++z) {
			for (GLuint x = 0; x < pointsPerSide - 1; ++x) {
				GLuint start = z * pointsPerSide + x;
				GLuint end = start + 1;
				indices.insert(indices.end(), {start, end});
			}
		}

		// Link those points together 2x2 to create vertical lines
		for (GLuint x = 0; x < pointsPerSide; ++x) {
			for (GLuint z = 0; z < pointsPerSide - 1; ++z) {
				GLuint start = z * pointsPerSide + x;
				GLuint end = start + pointsPerSide;
				indices.insert(indices.end(), {start, end});
			}
		}
	}
}
