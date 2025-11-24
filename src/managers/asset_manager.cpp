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
			mesh->vertices = {
				// positions          // normals
				// Front face
				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

				// Back face
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

				// Left face
				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
				-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

				// Right face
				0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
				0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
				0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

				// Top face
				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
				0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,

				// Bottom face
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
				0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f
			};
			mesh->vertexCount = 36;
		} else if (meshID == "grid") {
			int m_size = 100;
			float m_spacing = 3.5f;

			// Create individual points at each vertex in the grid
			for (int z = -m_size; z < m_size; ++z) {
				for (int x = -m_size; x < m_size; ++x) {
					GLfloat xPos = x * m_spacing;
					GLfloat zPos = z * m_spacing;
					mesh->vertices.insert(mesh->vertices.end(), {xPos, 0.f, zPos});
				}
			}

			GLuint pointsPerSide = m_size * 2;

			// Link those points together 2x2 to create horizontal lines
			for (GLuint z = 0; z < pointsPerSide; ++z) {
				for (GLuint x = 0; x < pointsPerSide - 1; ++x) {
					GLuint start = z * pointsPerSide + x;
					GLuint end = start + 1;
					mesh->indices.insert(mesh->indices.end(), {start, end});
				}
			}

			// Link those points together 2x2 to create vertical lines
			for (GLuint x = 0; x < pointsPerSide; ++x) {
				for (GLuint z = 0; z < pointsPerSide - 1; ++z) {
					GLuint start = z * pointsPerSide + x;
					GLuint end = start + pointsPerSide;
					mesh->indices.insert(mesh->indices.end(), {start, end});
				}
			}
			mesh->vertexCount = mesh->indices.size();
			mesh->useElements = true;
			mesh->drawMode = GL_LINES;
			mesh->useNormals = false;
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
		if (materialID == "simple") {
			material->shaderID = "simple";
		} else if (materialID == "grid") {
			material->shaderID = "grid";
		} else if (materialID == "light") {
			material->shaderID = "light";
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
}
