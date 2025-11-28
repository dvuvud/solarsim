#pragma once

#include <scene/entity.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <imgui.h>

namespace solarsim {
	class Registry;

	/**
	 * @brief Handles all rendering operations and graphics state
	 * 
	 * @note Manages UBOs for camera, lights, and rigid bodies
	 * @warning Ensure OpenGL context is active before calling render methods
	 */
	class Renderer {
		public:
			Renderer();
			~Renderer();

			/**
			 * @brief Execute one frame of rendering
			 * 
			 * @note Binds all UBOs and renders grid and meshes
			 * @warning Call this only from the main thread with active GL context
			 */
			void render();

			/**
			 * @brief Toggle grid visibility
			 */
			void toggleGrid() { showGrid = !showGrid; }

			/** Camera uniform buffer object */
			struct CameraUBO {
				glm::vec3 pos; float pad0;
				glm::mat4 view;
				glm::mat4 proj;
				glm::mat4 viewProj;
			};

			/** Single light source data */
			struct LightData {
				/** Stores the position of the light in xyz, w = padding */
				glm::vec4 pos;
				/** Stores the RGB values of the light in xyz and radius in w */
				glm::vec4 color;
			};

			/** Lights uniform buffer objects data */
			struct LightsUBO {
				LightData lights[64];
				int count = 0;
				float pad0[3];
			};

			/** Single rigid body data */
			struct RBData {
				/** Stores the position in x, y, z, and mass in w */
				glm::vec4 mPos;
			};

			/** Rigid bodies uniform buffer object data */
			struct RBUBO {
				RBData rbs[64];
				int count = 0;
				float pad0[3];
			};

		private:
			/**
			 * @brief Bind camera matrices to UBO
			 * @param reg Registry containing camera entities
			 */
			void bindCameraMatrices(Registry& reg);
			/**
			 * @brief Bind light data to UBO
			 * @param reg Registry containing light entities
			 */
			void bindLightUBOS(Registry& reg);
			/**
			 * @brief Bind rigid body data to UBO
			 * @param reg Registry containing rigid body entities
			 */
			void bindRigidBodyUBOS(Registry& reg);

			/**
			 * @brief Render the debug grid
			 * @param reg Registry containing grid entities
			 */
			void renderGrid(Registry& reg);

			/**
			 * @brief Render all light entities
			 * @param reg Registry containing mesh entities
			 */
			void renderLights(Registry& reg);

			/**
			 * @brief Render all mesh entities
			 * @param reg Registry containing mesh entities
			 */
			void renderMeshes(Registry& reg);

			/**
			 * @brief Toggle grid visibility
			 */
			void renderGui(Registry& reg);

			/** OpenGL handle for camera UBO */
			uint32_t cameraUBO;
			/** OpenGL handle for lights UBO */
			uint32_t lightsUBO;
			/** OpenGL handle for rigid bodies UBO */
			uint32_t rbUBO;
			/** Whether to render the debug grid */
			bool showGrid = true;
	};

}

