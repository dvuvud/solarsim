#include <glad/glad.h>
#include <graphics/material.hpp>
#include <mesh/mesh.hpp>
#include <components/mesh_component.hpp>

namespace solarsim {
	void MeshComponent::render() const {
		if (!m_meshAsset || !m_materialAsset) return;
		m_materialAsset->apply();
		m_meshAsset->render();
	}
}
