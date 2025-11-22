#include <systems/physics_system.hpp>

#include <scene/scene.hpp>
#include <managers/scene_manager.hpp>

#include <components/rigid_body_component.hpp>
#include <components/transform_component.hpp>

namespace solarsim {
	void PhysicsSystem::update(float deltaTime) {
		Scene* scene = SceneManager::get().active();
		if (!scene || scene->paused) return;
		deltaTime = scene->reverse ? -deltaTime : deltaTime;


		auto& registry = scene->registry;
		auto entities = registry.view<Rigidbodycomponent, TransformComponent>();

		std::vector<glm::vec3> accumulatedForces(entities.size(), glm::vec3(0.0f));

		for (size_t i = 0; i < entities.size(); ++i) {
			auto& rbA = registry.getComponent<Rigidbodycomponent>(entities[i]);
			auto& tfA = registry.getComponent<TransformComponent>(entities[i]);

			for (size_t j = i + 1; j < entities.size(); ++j) {
				auto& rbB = registry.getComponent<Rigidbodycomponent>(entities[j]);
				auto& tfB = registry.getComponent<TransformComponent>(entities[j]);

				glm::vec3 dir = tfB.position - tfA.position;
				float distSq = glm::dot(dir, dir);
				dir = glm::normalize(dir);

				float softenedDistSq = distSq + SOFTENING_SQUARED;
				float forceMag = G * (rbA.mass * rbB.mass) / softenedDistSq;
				glm::vec3 force = dir * forceMag;

				accumulatedForces[i] += force;
				accumulatedForces[j] -= force;
			}
		}

		// Apply velocities after accumulation
		for (int i = 0; i < entities.size(); ++i) {
			auto& rb = registry.getComponent<Rigidbodycomponent>(entities[i]);
			auto& tf = registry.getComponent<TransformComponent>(entities[i]);

			glm::vec3 acceleration = accumulatedForces[i] / rb.mass;
			rb.vel += acceleration * deltaTime;
			tf.position += rb.vel * deltaTime;
			tf.dirty = true;
		}
	}
}
