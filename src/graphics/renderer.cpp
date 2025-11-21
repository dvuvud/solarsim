#include "glad/glad.h"
#include <graphics/renderer.hpp>
#include <simulation/simulation.hpp>
#include <iostream>

namespace solarsim {
	Renderer::Renderer()
	{
		glEnable(GL_DEPTH_TEST);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Renderer::render(const Simulation* p_sim, const Camera* p_cam) const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (!p_sim || !p_cam) return;
	}

