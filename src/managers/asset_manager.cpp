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
		}

		mesh->setupBuffers();
		loadedMeshes[meshID] = mesh;
		return mesh;
	}
	std::shared_ptr<Material> AssetManager::LoadMaterial(const std::string& materialID) {
		auto it = loadedMaterials.find(materialID);
		if (it != loadedMaterials.end()) return it->second;

		// TODO: Add functionality for loading materials
		auto material = std::make_shared<Material>();
		if (materialID == "simple1") {
			material->shaderID = "simple";
		} else if (materialID == "simple2") {
			material->shaderID = "simple";
			material->albedo = glm::vec3(1.0f, 0.0f, 0.0f);
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
