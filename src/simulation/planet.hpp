#pragma once

#include "entity.hpp"

class Planet : public Entity {
	public:
		Planet(Mesh* mesh = nullptr, Material* material = nullptr, const glm::vec3& position = glm::vec3(0.0f));
		virtual ~Planet() = default;
		void update(float deltaTime) override;
		virtual void render(Shader& shader) override;
};
