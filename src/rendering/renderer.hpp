#pragma once

#include "../core/camera.hpp"
#include "../graphics/shader.hpp"
#include "../simulation/entity.hpp"

class Renderer {
	private:
		std::vector<std::unique_ptr<Entity>>& entities;

	public:
		Renderer(std::vector<std::unique_ptr<Entity>>& entities);
		~Renderer() = default;
		void render(const Camera& camera);
};
