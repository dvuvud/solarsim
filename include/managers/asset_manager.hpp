#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <graphics/mesh.hpp>
#include <graphics/material.hpp>
#include <graphics/shader.hpp>

namespace solarsim {
	class AssetManager {
		public:
			AssetManager(const AssetManager&) = delete;
			AssetManager& operator=(const AssetManager&) = delete;

			static AssetManager& get() {
				static AssetManager instance;
				return instance;
			}

			std::shared_ptr<Mesh> LoadMesh(const std::string& meshID) {
				auto it = loadedMeshes.find(meshID);
				if (it != loadedMeshes.end()) return it->second;
				
				// TODO: Implement assimp and replace the following with model loading
				auto mesh = std::make_shared<Mesh>();
				loadedMeshes[meshID] = mesh;
				return mesh;
			}
			std::shared_ptr<Material> LoadMaterial(const std::string& materialID) {
				auto it = loadedMaterials.find(materialID);
				if (it != loadedMaterials.end()) return it->second;

				// TODO: Add functionality for loading materials
				auto material = std::make_shared<Material>();
				loadedMaterials[materialID] = material;
				return material;
			}
			std::shared_ptr<Shader> LoadShader(const std::string& shaderID) {
				auto it = loadedShaders.find(shaderID);
				if (it != loadedShaders.end()) return it->second;

				auto shader = std::make_shared<Shader>();
				shader->programID = compileShader(shaderID);
				loadedShaders[shaderID] = shader;
				return shader;
			}

		private:
			std::unordered_map<std::string, std::shared_ptr<Material>> loadedMaterials;
			std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;
			std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;

			unsigned int compileShader(const std::string& shaderID);

			AssetManager() {}
			~AssetManager() {}
	};
}
