#pragma once

#include "component.hpp"
#include <string>
#include <memory>
#include <factories/mesh_factory.hpp>
#include <factories/material_factory.hpp>

namespace solarsim {
	class Mesh;
	class Material;
	class MeshComponent : public Component {
		public:
			std::shared_ptr<Mesh> _meshAsset;
			std::shared_ptr<Material> _materialAsset;
			MeshComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) : _meshAsset(mesh), _materialAsset(material) {}
			MeshComponent(const std::string& meshID, const std::string& materialID) :
				_meshAsset(MeshFactory::get().LoadMesh(meshID)), _materialAsset(MaterialFactory::get().LoadMaterial(materialID)) {}
			void render() const;
	};
}
