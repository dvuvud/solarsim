#include <glad/glad.h>
#include <engine/renderer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <scene/registry.hpp>
#include <components/mesh_component.hpp>
#include <components/transform_component.hpp>
#include <components/camera_component.hpp>
#include <managers/asset_manager.hpp>
#include <managers/scene_manager.hpp>

namespace solarsim {
	void Renderer::render() {
		Scene* scene = SceneManager::get().active();
		if (!scene) return;

		const Registry& registry = scene->registry;
		Entity cameraEntity = getPrimaryCamera(registry);
		if (cameraEntity == -1) return;

		auto& camTransform = registry.getComponent<TransformComponent>(cameraEntity);
		auto& cam = registry.getComponent<CameraComponent>(cameraEntity);

		glm::mat4 view = glm::lookAt(camTransform.position,
				camTransform.position + glm::vec3(0,0,-1),
				glm::vec3(0,1,0));
		glm::mat4 projection = glm::perspective(glm::radians(cam.fov),
				cam.aspect, cam.near, cam.far);

		for (Entity e : registry.view<TransformComponent, MeshComponent>()) {
			auto& transform = registry.getComponent<TransformComponent>(e);
			auto& meshComp = registry.getComponent<MeshComponent>(e);

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
			// Could for example loop over registry.view(TransformComponent, LightComponent>()

			// TODO: Move options like the following over to mesh
			glBindVertexArray(mesh->vao);
			glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);
		}
	}

	Entity Renderer::getPrimaryCamera(const Registry& registry) {
		for (Entity e : registry.view<TransformComponent, CameraComponent>()) {
			auto& cam = registry.getComponent<CameraComponent>(e);
			if (cam.primary) return e;
		}
		return -1;
	}
}
