#include <managers/asset_manager.hpp>
#include <graphics/mesh.hpp>
#include <graphics/material.hpp>
#include <graphics/shader.hpp>

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
		loadedMeshes[meshID] = mesh;
		return mesh;
	}
	std::shared_ptr<Material> AssetManager::LoadMaterial(const std::string& materialID) {
		auto it = loadedMaterials.find(materialID);
		if (it != loadedMaterials.end()) return it->second;

		// TODO: Add functionality for loading materials
		auto material = std::make_shared<Material>();
		loadedMaterials[materialID] = material;
		return material;
	}
	std::shared_ptr<Shader> AssetManager::LoadShader(const std::string& shaderID) {
		auto it = loadedShaders.find(shaderID);
		if (it != loadedShaders.end()) return it->second;

		auto shader = std::make_shared<Shader>();
		shader->programID = compileShader(shaderID);
		loadedShaders[shaderID] = shader;
		return shader;
	}

	unsigned int AssetManager::compileShader(const std::string& shaderID) {
		return 0;
	}
}
