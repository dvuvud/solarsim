#pragma once

#include <unordered_map>
#include <string>
#include <mesh/cube.hpp>
#include <graphics/material.hpp>

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
				if (it != loadedMeshes.end()) {
					return it->second;
				}
				// TODO: Implement assimp and replace the following with model loading
				std::shared_ptr<Cube> mesh = std::make_shared<Cube>();
				loadedMeshes[meshID] = mesh;
				return mesh;
			}
			std::shared_ptr<Material> LoadMaterial(const std::string& materialID) {
				auto it = loadedMaterials.find(materialID);
				if (it != loadedMaterials.end()) {
					return it->second;
				}
				// TODO: Add functionality for loading materials
				auto material = std::make_shared<Material>();
				loadedMaterials[materialID] = material;
				return material;
			}

		private:
			std::unordered_map<std::string, std::shared_ptr<Material>> loadedMaterials;
			std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;

			AssetManager() {}
			~AssetManager() {}
	};
}
