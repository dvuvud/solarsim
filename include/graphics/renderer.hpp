#pragma once

#include <vector>
#include <memory>

namespace solarsim {
	class Camera;
	class Simulation;
	class Renderer {
		public:
			Renderer();
			~Renderer() = default;
			void render(const Simulation* p_sim, const Camera* p_cam) const;
	};
}
