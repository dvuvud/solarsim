#pragma once

#include <scene/entity.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace solarsim {
	class Registry;
	class Renderer {
		public:
			Renderer();
			~Renderer();
			void render();
			void toggleGrid() { showGrid = !showGrid; }

			struct CameraUBO {
				glm::vec3 pos; float pad0;
				glm::mat4 view;
				glm::mat4 proj;
				glm::mat4 viewProj;
			};

			struct LightData {
				glm::vec4 pos;
				glm::vec4 color;
			};

			struct LightsUBO {
				LightData lights[64];
				int count = 0;
				float pad0[3];
			};

			struct RBData {
				glm::vec4 mPos;
			};

			struct RBUBO {
				RBData rbs[64];
				int count = 0;
				float pad0[3];
			};

		private:
			void bindCameraMatrices(Registry& reg);
			void bindLightUBOS(Registry& reg);
			void bindRigidBodyUBOS(Registry& reg);
			void renderGrid(Registry& reg);
			void renderMeshes(Registry& reg);
			unsigned int cameraUBO;
			unsigned int lightsUBO;
			unsigned int rbUBO;
			bool showGrid = true;
	};

}

