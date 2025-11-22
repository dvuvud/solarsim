#include <managers/scene_manager.hpp>

#include <scene/scene.hpp>

namespace solarsim {
	SceneManager& SceneManager::get() {
		static SceneManager instance;
		return instance;
	}

	Scene* SceneManager::active() {
		return activeScene;
	}

	void SceneManager::setActive(Scene* scene) {
		activeScene = scene;
	}
}
