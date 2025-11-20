#pragma once

#include <unordered_map>
#include <string>
#include <mesh/cube.hpp>

namespace solarsim {
	class MeshFactory {
		public:
			MeshFactory(const MeshFactory&) = delete;
			MeshFactory& operator=(const MeshFactory&) = delete;

			static MeshFactory& get() {
				static MeshFactory instance;
				return instance;
			}

			Mesh* loadMesh(const std::string& meshID) {
				auto it = loadedMeshes.find(meshID);
				if (it != loadedMeshes.end()) {
					return it->second;
				}
				// TODO: Implement assimp and replace the following with model loading
				Mesh* mesh = new Cube();
				loadedMeshes[meshID] = mesh;
				return mesh;
			}
		private:
			MeshFactory() {}
			~MeshFactory() {}
			std::unordered_map<std::string, Mesh*> loadedMeshes;
	};
}
