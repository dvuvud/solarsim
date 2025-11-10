#pragma once

#include <graphics/camera.hpp>
#include <graphics/shader.hpp>
#include <simulation/entity.hpp>

class Renderer {
	public:
		Renderer(std::vector<std::unique_ptr<Entity>>& entities, const Camera* camera = nullptr);
		~Renderer() = default;
		void render();
		void setActiveCamera(const Camera* camera) { activeCamera = camera; }
	private:
		std::vector<std::unique_ptr<Entity>>& entities;
		const Camera* activeCamera;
};
