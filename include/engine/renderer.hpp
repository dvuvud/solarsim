#pragma once

#include <optional>
#include <scene/entity.hpp>

namespace solarsim {
	class Registry;

	class Renderer {
		public:
			void render();
		private:
			std::optional<Entity> getPrimaryCamera(Registry& registry);
	};

}

