#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/registry.hpp>
#include <components/mesh_component.hpp>
#include <components/transform_component.hpp>
#include <components/camera_component.hpp>
#include <managers/asset_manager.hpp>

namespace solarsim {

	class Renderer {
		public:
			Renderer(Registry& registry) : m_registry(registry) {}

			void drawScene() {
				Entity cameraEntity = getPrimaryCamera();
				if (cameraEntity == -1) return;

				auto& camTransform = m_registry.getComponent<TransformComponent>(cameraEntity);
				auto& cam = m_registry.getComponent<CameraComponent>(cameraEntity);

				glm::mat4 view = glm::lookAt(camTransform.position,
						camTransform.position + glm::vec3(0,0,-1),
						glm::vec3(0,1,0));
				glm::mat4 projection = glm::perspective(glm::radians(cam.fov),
						cam.aspect, cam.near, cam.far);

				for (Entity e : m_registry.view<TransformComponent, MeshComponent>()) {
					auto& transform = m_registry.getComponent<TransformComponent>(e);
					auto& meshComp = m_registry.getComponent<MeshComponent>(e);

					glm::mat4 model = transform.getModelMatrix();
					glm::mat4 mvp = projection * view * model;

					// TODO: Add logs when things go wrong
					auto mesh = AssetManager::get().LoadMesh(meshComp.meshID);
					if (!mesh) continue;
					auto material = AssetManager::get().LoadMaterial(meshComp.materialID);
					if (!material) continue;
					auto shader = AssetManager::get().LoadShader(material->shaderID);
					if (!shader) continue;

					shader->use();
					shader->setUniform("uMVP", mvp);
					// Set other uniforms like applying materials and light materials etc
					// Could for example loop over m_registry.view(TransformComponent, LightComponent>()

					// TODO: Move options like the following over to mesh
					glBindVertexArray(mesh->vao);
					glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
				}
			}

		private:
			Registry& m_registry;

			Entity getPrimaryCamera() {
				for (Entity e : m_registry.view<TransformComponent, CameraComponent>()) {
					auto& cam = m_registry.getComponent<CameraComponent>(e);
					if (cam.primary) return e;
				}
				return -1;
			}
	};

}

