#pragma once

#include <string>

namespace solarsim {
	/**
	 * @brief Associates an entity with renderable geometry and appearance
	 * 
	 * @note Similar to GridComponent but for general 3D models
	 */
	struct MeshComponent {
		/** Identifier for the mesh geometry resource */
		std::string meshID;

		/** Identifier for the material/shader resource */
		std::string materialID;
	};
}
