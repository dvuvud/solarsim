#pragma once

#include "../core/camera.hpp"
#include "../graphics/shader.hpp"
#include "../simulation/entity.hpp"

class Renderer {
	private:
		std::unordered_map<Shader*, std::vector<std::unique_ptr<Entity>>> renderGroups;

	public:
		Renderer();
		~Renderer();
		void init();
		void render(const Camera& camera);
		void registerEntity(std::unique_ptr<Entity> obj);
};

