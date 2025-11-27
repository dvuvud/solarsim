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

#include <engine/engine.hpp>

namespace solarsim {
	Renderer::Renderer() {
		// -- INIT CAMERA UBO --
		glGenBuffers(1, &cameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUBO), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUBO);

		// -- INIT LIGHT UBO --
		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(LightsUBO), nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightsUBO);

		// -- INIT RIGID BODY UBO --
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
	void Renderer::render() {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Scene* scene = SceneManager::get().active();
		if (!scene) return;

		Registry& registry = scene->registry;

		bindCameraMatrices(registry);
		bindLightUBOS(registry);
		bindRigidBodyUBOS(registry);

		if (showGrid) {
			glEnable(GL_BLEND); // Couple objects that need transparency for the future
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			renderGrid(registry);
			glDisable(GL_BLEND);
		}
		renderMeshes(registry);
	}

	void Renderer::bindCameraMatrices(Registry& reg) {
		auto cameraEntityOpt = Engine::getPrimaryCamera(reg);
		if (cameraEntityOpt == -1) return;
		Entity cameraEntity = *cameraEntityOpt;

		auto& camTransform = reg.getComponent<TransformComponent>(cameraEntity);
		auto& cam = reg.getComponent<CameraComponent>(cameraEntity);

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
	}

	void Renderer::bindLightUBOS(Registry& reg) {
		LightsUBO L;
		for (auto e : reg.view<TransformComponent, LightComponent>()) {
			if (L.count >= 64) break;
			TransformComponent& LT = reg.getComponent<TransformComponent>(e);
			LightComponent& LC = reg.getComponent<LightComponent>(e);

			L.lights[L.count].color = glm::vec4(LC.color, LC.radius);
			L.lights[L.count].pos = glm::vec4(LT.position, 0.0);
			++L.count;
		}
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(LightsUBO), &L);
	}

	void Renderer::bindRigidBodyUBOS(Registry& reg) {
		RBUBO RB;
		for (auto e : reg.view<TransformComponent, RigidBodyComponent>()) {
			if (RB.count >= 64) break;
			auto& TC = reg.getComponent<TransformComponent>(e);
			auto& RBC = reg.getComponent<RigidBodyComponent>(e);

			RB.rbs[RB.count].mPos.x = TC.position.x;
			RB.rbs[RB.count].mPos.y = TC.position.y;
			RB.rbs[RB.count].mPos.z = TC.position.z;
			RB.rbs[RB.count].mPos.w = RBC.mass;
			++RB.count;
		}
		glBindBuffer(GL_UNIFORM_BUFFER, rbUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(RBUBO), &RB);
	}

	void Renderer::renderGrid(Registry& reg) {
		for (auto e : reg.view<GridComponent>()) {
			auto& meshComp = reg.getComponent<GridComponent>(e);

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
	}

	void Renderer::renderMeshes(Registry& reg) {
		for (auto e : reg.view<TransformComponent, MeshComponent>()) {
			auto& transform = reg.getComponent<TransformComponent>(e);
			auto& meshComp = reg.getComponent<MeshComponent>(e);

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

			glBindVertexArray(mesh->vao);
			if (mesh->useElements)
				glDrawElements(mesh->drawMode, mesh->vertexCount, GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(mesh->drawMode, 0, mesh->vertexCount);
		}
	}
}
