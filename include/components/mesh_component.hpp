#pragma once

#include "component.hpp"

namespace solarsim {
	class Mesh;
	class Material;
	class MeshComponent : public Component {
		public:
			Mesh* m_meshAsset;
			Material* m_materialAsset;
			void draw();
	};
}
