#pragma once

#include <scene/scene.hpp>

namespace solarsim {
	class SceneManager {
		public:
			static Scene& getActiveScene() {
				return activeScene;
			}
		private:
			mutable Scene activeScene;
			SceneManager() {}
			~SceneManager() {}
	};
}
