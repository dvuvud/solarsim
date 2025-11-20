#pragma once

#include <unordered_map>
#include <graphics/material.hpp>

namespace solarsim {
	class MaterialFactory {
		public:
			MaterialFactory(const MaterialFactory&) = delete;
			MaterialFactory& operator=(const MaterialFactory&) = delete;

			static MaterialFactory& get() {
				static MaterialFactory instance;
				return instance;
			}

			std::shared_ptr<Material> loadMaterial(const std::string& materialID) {
				auto it = loadedMaterials.find(materialID);
				if (it != loadedMaterials.end()) {
					return it->second;
				}
				// TODO: Add functionality for loading materials
				auto material = std::make_shared<Material>(materialID);
				return material;
			}
		private:
			MaterialFactory() {}
			~MaterialFactory() {}
			std::unordered_map<std::string, std::shared_ptr<Material>> loadedMaterials;
	}
}
