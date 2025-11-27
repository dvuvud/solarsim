#pragma once

#include <memory>
#include <optional>
#include "scene/entity.hpp"

namespace solarsim {
	class Window;
	class Renderer;
	class InputSystem;
	class PhysicsSystem;
	struct Registry;

	/**
	 * @brief Main engine class managing core systems and game loop
	 */
	class Engine {
		public:
			Engine(const Engine&) = delete;
			Engine& operator=(const Engine&) = delete;

			/**
			 * @brief Get the singleton engine instance
			 * @return Engine& Reference to the engine instance
			 */
			static Engine& get() {
				static Engine instance;
				return instance;
			}

			/**
			 * @brief Start the main game loop
			 * 
			 * @note This method blocks until the application exits
			 */
			void run();

			// System accessors
			Window* window() const { return m_window.get(); }
			Renderer* renderer() const { return m_renderer.get(); }
			InputSystem* inputManager() const { return m_inputSystem.get(); }
			PhysicsSystem* physicsSystem() const { return m_physicsSystem.get(); }

			/**
			 * @brief Find the primary camera entity in the registry
			 * @param registry The registry to search in
			 * @return std::optional<Entity> The primary camera entity if found
			 * 
			 * @note Looks for CameraComponent with primary=true
			 */
			static std::optional<Entity> getPrimaryCamera(Registry& registry);
		private:
			Engine();
			~Engine();

			/**
			 * @brief Initialize all engine subsystems
			 */
			void init();

			/** Window management system */
			std::unique_ptr<Window> m_window;
			/** Rendering system */
			std::unique_ptr<Renderer> m_renderer;

			/** Input processing system */
			std::unique_ptr<InputSystem> m_inputSystem;
			/** Physics handling system */
			std::unique_ptr<PhysicsSystem> m_physicsSystem;
	};
}
