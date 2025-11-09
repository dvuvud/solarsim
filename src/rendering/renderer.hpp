#pragma once

#include "../core/camera.hpp"
#include "../graphics/shader.hpp"
#include "../simulation/entity.hpp"

class Renderer {
	private:
		std::unordered_map<Shader*, std::vector<std::vector<Entity*>>> renderGroups;

	public:
		Renderer() = default;
		~Renderer() = default;
		void init();
		void render(const Camera& camera);
		void registerEntity(std::vector<Entity*> obj);
};

