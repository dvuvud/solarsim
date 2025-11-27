#pragma once

#include <string>

namespace solarsim {
	/**
	 * @brief Represents a grid/mesh for rendering with specific assets
	 */
	struct GridComponent {
		/** Identifier for the mesh resource to use */
		std::string meshID;

		/** Identifier for the material resource to us */
		std::string materialID;
	};
}
