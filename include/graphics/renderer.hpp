#pragma once

#include <graphics/camera.hpp>
#include <graphics/shader.hpp>
#include <simulation/entity.hpp>
#include <memory>

class Renderer {
	public:
		Renderer(const std::vector<std::unique_ptr<Entity>>& entities, Camera* camera = nullptr);
		~Renderer() = default;
		void render();
		void setActiveCamera(Camera* camera) { activeCamera = camera; }
	private:
		const std::vector<std::unique_ptr<Entity>>& entities;
		Camera* activeCamera;
};
