#include <managers/scene_manager.hpp>

namespace solarsim {
	SceneManager& SceneManager::get() {
		static SceneManager instance;
		return instance;
	}

	Scene* SceneManager::active() {
		return m_activeScene.get();
	}

	void SceneManager::loadScene(std::unique_ptr<Scene> newScene) {
		m_activeScene = std::move(newScene);
	}

	void SceneManager::unloadScene() {
		m_activeScene.reset();
	}
}
