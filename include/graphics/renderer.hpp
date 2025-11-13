#pragma once

#include <vector>
#include <memory>

namespace solarsim {
	class Camera;
	class Entity;
	class Renderer {
		public:
			Renderer();
			~Renderer() = default;
			void render(const std::vector<std::unique_ptr<Entity>>& p_entities, const Camera* p_camera) const;
	};
}
