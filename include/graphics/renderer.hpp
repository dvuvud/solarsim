#pragma once

#include <memory>

namespace solarsim {
	class Camera;
	class Entity;
	class Renderer {
		public:
			Renderer(const std::vector<Entity*>& entities, Camera* camera = nullptr);
			~Renderer() = default;
			void render();
			void setActiveCamera(Camera* camera) { activeCamera = camera; }
		private:
			const std::vector<Entity*>& entities;
			Camera* activeCamera;
	};
}
