#include <systems/physics_system.hpp>

#include <scene/scene.hpp>
#include <managers/scene_manager.hpp>

#include <iostream>

namespace solarsim {
	void PhysicsSystem::update(float deltaTime) {
		Scene* scene = SceneManager::get().active();
		if (!scene) return;
		// Get scene from scene manager
		//
		// Get registry from scene
		//
		// Get entities with rigid body and transform from registry
		//
		// Calculate gravity and other physics with helper functions
		//
		// Update struct data
	}
}
