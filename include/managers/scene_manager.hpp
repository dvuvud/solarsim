#pragma once

namespace solarsim {
	class SceneManager {
		public:
			static Scene& getActiveScene() {
				static Scene activeScene;
				return activeScene;
			}
		private:
			SceneManager() {}
			~SceneManager() {}
	};
}
