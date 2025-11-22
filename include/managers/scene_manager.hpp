#pragma once

#include <memory>

namespace solarsim {
	struct Scene;
	class SceneManager {
		public:
			SceneManager(const SceneManager&) = delete;
			SceneManager& operator=(const SceneManager&) = delete;

			static SceneManager& get();

			Scene* active();

			void loadScene(std::unique_ptr<Scene> newScene);
			void unloadScene();
		private:
			std::unique_ptr<Scene> m_activeScene;
			SceneManager() {}
			~SceneManager() {}
	};
}
