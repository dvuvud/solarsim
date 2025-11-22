#pragma once

#include <scene/entity.hpp>

namespace solarsim {
	class Registry;

	class Renderer {
		public:
			void render();
		private:
			Entity getPrimaryCamera(const Registry& registry);
	};

}

