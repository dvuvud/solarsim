#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <graphics/shader.hpp>
#include <graphics/material.hpp>
#include <graphics/camera.hpp>
#include <simulation/entity.hpp>

namespace solarsim {
	Renderer::Renderer()
	{
		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Renderer::render(const std::vector<Entity*>& p_entities, const Camera* p_camera)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!p_camera) return;
		for (Entity* entity : p_entities) {
			if (entity) entity->render(*p_camera);
		}
	}
}
