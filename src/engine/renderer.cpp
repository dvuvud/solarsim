#include <glad/glad.h>
#include <engine/renderer.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <components/mesh_component.hpp>
#include <components/grid_component.hpp>
#include <components/transform_component.hpp>
#include <components/light_component.hpp>
#include <components/camera_component.hpp>
#include <components/rigid_body_component.hpp>

#include <managers/asset_manager.hpp>
#include <managers/scene_manager.hpp>

#include <scene/registry.hpp>
#include <scene/scene.hpp>

#include <graphics/material.hpp>
#include <graphics/shader.hpp>
#include <graphics/mesh.hpp>

namespace solarsim {
	Renderer::Renderer() {
		glGenBuffers(1, &cameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUBO), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUBO);

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(LightsUBO), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightsUBO);

		glGenBuffers(1, &rbUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, rbUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(RBUBO), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 2, rbUBO);
	}
	Renderer::~Renderer() {
		glDeleteBuffers(1, &cameraUBO);
		glDeleteBuffers(1, &lightsUBO);
		glDeleteBuffers(1, &rbUBO);
	}
	// TODO: REFACTOR METHOD ASAP
	void Renderer::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Scene* scene = SceneManager::get().active();
		if (!scene) return;

		Registry& registry = scene->registry;

		// ------- BIND CAMERA MATRICES --------
		auto cameraEntityOpt = getPrimaryCamera(registry);
		if (cameraEntityOpt == -1) return;
		Entity cameraEntity = *cameraEntityOpt;

		auto& camTransform = registry.getComponent<TransformComponent>(cameraEntity);
		auto& cam = registry.getComponent<CameraComponent>(cameraEntity);

		glm::vec3 forward = camTransform.rotation * glm::vec3(0, 0, -1);

		CameraUBO camUBO;
		camUBO.pos = camTransform.position;
		camUBO.view = glm::lookAt(
				camTransform.position,
				camTransform.position + forward,
				camTransform.rotation * glm::vec3(0, 1, 0)
				);
		camUBO.proj = glm::perspective(glm::radians(cam.fov),
				cam.aspect, cam.near, cam.far);
		camUBO.viewProj = camUBO.proj * camUBO.view;

		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraUBO), &camUBO);

		// ------- GET AND BIND ALL LIGHT UBOS -------
		LightsUBO L;
		for (auto e : registry.view<TransformComponent, LightComponent>()) {
			if (L.count >= 64) break;
			TransformComponent& LT = registry.getComponent<TransformComponent>(e);
			LightComponent& LC = registry.getComponent<LightComponent>(e);

			L.lights[L.count].color = glm::vec4(LC.color, LC.radius);
			L.lights[L.count].pos = glm::vec4(LT.position, 0.0);
			++L.count;
		}
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightsUBO), &L);

		// ------- GET AND BIND ALL RIGID BODY UBOS -------
		RBUBO RB;
		for (auto e : registry.view<TransformComponent, RigidBodyComponent>()) {
			if (RB.count >= 64) break;
			auto& TC = registry.getComponent<TransformComponent>(e);
			auto& RBC = registry.getComponent<RigidBodyComponent>(e);

			RB.rbs[RB.count].mPos.x = TC.position.x;
			RB.rbs[RB.count].mPos.y = TC.position.y;
			RB.rbs[RB.count].mPos.z = TC.position.z;
			RB.rbs[RB.count].mPos.w = RBC.mass;
			++RB.count;
		}
		glBindBuffer(GL_UNIFORM_BUFFER, rbUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(RBUBO), &RB);

		// ------- RENDER GRID --------
		for (auto e : registry.view<GridComponent>()) {
			auto& meshComp = registry.getComponent<GridComponent>(e);

			auto mesh = AssetManager::get().LoadMesh(meshComp.meshID);
			auto material = AssetManager::get().LoadMaterial(meshComp.materialID);
			if (!mesh || !material) continue;
			auto shader = AssetManager::get().LoadShader(material->shaderID);
			if (!shader) return;

			shader->use();

			shader->setUniform("uMaterial.albedo", material->albedo);
			shader->setUniform("uMaterial.metallic", material->metallic);
			shader->setUniform("uMaterial.roughness", material->roughness);

			glBindVertexArray(mesh->vao);
			if (mesh->useElements)
				glDrawElements(mesh->drawMode, mesh->vertexCount, GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(mesh->drawMode, 0, mesh->vertexCount);
		}


		// ------- RENDER MESHES --------
		for (auto e : registry.view<TransformComponent, MeshComponent>()) {
			auto& transform = registry.getComponent<TransformComponent>(e);
			auto& meshComp = registry.getComponent<MeshComponent>(e);

			glm::mat4 model = transform.getModelMatrix();

			// TODO: Add logs for when things go wrong
			auto mesh = AssetManager::get().LoadMesh(meshComp.meshID);
			auto material = AssetManager::get().LoadMaterial(meshComp.materialID);
			if (!mesh || !material) continue;
			auto shader = AssetManager::get().LoadShader(material->shaderID);
			if (!shader) continue;

			shader->use();
			shader->setUniform("uModel", model);

			shader->setUniform("uMaterial.albedo", material->albedo);
			shader->setUniform("uMaterial.metallic", material->metallic);
			shader->setUniform("uMaterial.roughness", material->roughness);

			// Set other uniforms like applying light etc
			// Could for example loop over registry.view(TransformComponent, LightComponent>()

			glBindVertexArray(mesh->vao);
			if (mesh->useElements)
				glDrawElements(mesh->drawMode, mesh->vertexCount, GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(mesh->drawMode, 0, mesh->vertexCount);
		}
	}

	std::optional<Entity> Renderer::getPrimaryCamera(Registry& registry) {
		for (auto e : registry.view<TransformComponent, CameraComponent>()) {
			auto& cam = registry.getComponent<CameraComponent>(e);
			if (cam.primary) return e;
		}
		return -1;
	}
}
