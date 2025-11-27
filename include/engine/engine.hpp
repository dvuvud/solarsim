#pragma once

#include <memory>
#include <optional>
#include "scene/entity.hpp"

namespace solarsim {
	class Window;
	class Renderer;
	class InputSystem;
	class PhysicsSystem;
	struct Scene;
	struct Registry;

	class Engine {
		public:
			Engine(const Engine&) = delete;
			Engine& operator=(const Engine&) = delete;

			static Engine& get() {
				static Engine instance;
				return instance;
			}

			void run();

			Window* window() const { return m_window.get(); }
			Renderer* renderer() const { return m_renderer.get(); }
			InputSystem* inputManager() const { return m_inputSystem.get(); }
			PhysicsSystem* physicsSystem() const { return m_physicsSystem.get(); }
			Scene* currentScene() const { return m_activeScene.get(); }

			void loadScene(std::unique_ptr<Scene> scene);

			static std::optional<Entity> getPrimaryCamera(Registry& registry);
		private:
			Engine();
			~Engine();

			void init();

			std::unique_ptr<Window> m_window;
			std::unique_ptr<Renderer> m_renderer;

			std::unique_ptr<InputSystem> m_inputSystem;
			std::unique_ptr<PhysicsSystem> m_physicsSystem;

			std::unique_ptr<Scene> m_activeScene;
	};
}
