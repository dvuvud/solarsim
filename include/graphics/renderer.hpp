#pragma once

#include <vector>
#include <memory>

namespace solarsim {
	class Camera;
	class Entity;
	class Simulation;
	class Grid;
	class FlammPoraboloid;
	class Renderer {
		public:
			Renderer();
			~Renderer() = default;
			void render(const std::unique_ptr<Simulation>& p_sim) const;
		private:
			void draw_entity(const std::unique_ptr<Entity>& p_entity, const Camera& p_camera) const;
			void draw_grid(const Grid& p_grid, const Camera& p_camera) const;
	};
}
