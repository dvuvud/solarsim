#pragma once

#include <memory>

namespace solarsim {
	struct Scene;

	/**
	 * @brief Manages scene lifecycle and transitions
	 * 
	 * @note Singleton pattern for global scene management
	 */
	class SceneManager {
		public:
			SceneManager(const SceneManager&) = delete;
			SceneManager& operator=(const SceneManager&) = delete;

			/**
			 * @brief Get the singleton SceneManager instance
			 * @return SceneManager& Reference to the scene manager
			 */
			[[nodiscard]] static SceneManager& get();

			/**
			 * @brief Get the currently active scene
			 * @return Scene* Pointer to active scene, or nullptr if none loaded
			 * 
			 * @warning Returns raw pointer so scene ownership remains with SceneManager
			 */
			[[nodiscard]] Scene* active();

			/**
			 * @brief Load a new scene, replacing the current one
			 * @param newScene Unique pointer to the scene to load
			 */
			void loadScene(std::unique_ptr<Scene> newScene);

			/**
			 * @brief Unload the current active scene
			 */
			void unloadScene();
		private:
			/** Currently active scene */
			std::unique_ptr<Scene> m_activeScene;

			SceneManager() {}
			~SceneManager() {}
	};
}
