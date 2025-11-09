#pragma once

#include "../core/camera.hpp"
#include "../graphics/shader.hpp"
#include "../simulation/entity.hpp"

class Renderer {
	private:
		std::unordered_map<Shader*, std::vector<Entity*>> renderBatches;

	public:
		Renderer() = default;
		~Renderer() = default;
		void render(const Camera& camera);
		void clearAllEntities();
		void registerEntity(Entity& obj);
};
