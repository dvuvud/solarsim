#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <memory>

namespace solarsim {

	class Mesh;
	class Material;
	class Shader;
	class Window;
	class Renderer;
	class InputManager;
	class Simulation;

	class Engine {
		public:
			Engine(unsigned int width = 800, unsigned int height = 600, const std::string& title = "solarsim");
			~Engine();
			void run();
		private:
			Window* window;
			Simulation* simulation;
			Renderer* renderer;
			InputManager* inputManager;

			// Temporary for testing, move to respective factories or similar
			Mesh* tmpMesh;
			Material* tmpMat;
			Shader* tmpShader;

			Material* tmpLightMat;
			Shader* tmpLightShader;
	};
}
