#pragma once

#include <optional>
#include <scene/entity.hpp>

namespace solarsim {
	class Registry;

	class Renderer {
		public:
			Renderer();
			~Renderer();
			void render();
		private:
			unsigned int cameraUBO;
			std::optional<Entity> getPrimaryCamera(Registry& registry);
	};

}

