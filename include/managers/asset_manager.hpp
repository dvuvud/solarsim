#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace solarsim {
	struct Mesh;
	struct Material;
	struct Shader;
	class AssetManager {
		public:
			AssetManager(const AssetManager&) = delete;
			AssetManager& operator=(const AssetManager&) = delete;

			static AssetManager& get();

			std::shared_ptr<Mesh> LoadMesh(const std::string& meshID);
			std::shared_ptr<Material> LoadMaterial(const std::string& materialID);
			std::shared_ptr<Shader> LoadShader(const std::string& shaderID);

		private:
			std::unordered_map<std::string, std::shared_ptr<Material>> loadedMaterials;
			std::unordered_map<std::string, std::shared_ptr<Mesh>> loadedMeshes;
			std::unordered_map<std::string, std::shared_ptr<Shader>> loadedShaders;

			AssetManager() {}
			~AssetManager() {}
	};
}
