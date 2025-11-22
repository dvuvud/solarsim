#pragma once

namespace solarsim {
	struct Scene;
	class SceneManager {
		public:
			SceneManager(const SceneManager&) = delete;
			SceneManager& operator=(const SceneManager&) = delete;

			static SceneManager& get();

			Scene* active();

			void setActive(Scene* scene);
		private:
			Scene* activeScene;
			SceneManager() {}
			~SceneManager() {}
	};
}
