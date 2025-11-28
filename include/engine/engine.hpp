#pragma once

#include <memory>
#include <optional>
#include <engine/window.hpp>
#include <engine/renderer.hpp>
#include <systems/input_system.hpp>
#include <systems/physics_system.hpp>
#include "scene/entity.hpp"

namespace solarsim {
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

			/** Const getter for the window management system */
			const Window& window() const { return m_window; }
			/** Non-const getter for the window management system */
			Window& window() { return m_window; }
			/** Const getter for the renderingsystem */
			const Renderer& renderer() const { return m_renderer; }
			/** Non-const getter for the renderingsystem */
			Renderer& renderer() { return m_renderer; }

			/** Const getter for the input management system */
			const InputSystem& inputManager() const { return m_inputSystem; }
			/** Non-const getter for the input management system */
			InputSystem& inputManager() { return m_inputSystem; }
			/** Const getter for the physics system */
			const PhysicsSystem& physicsSystem() const { return m_physicsSystem; }
			/** Non-const getter for the physics system */
			PhysicsSystem& physicsSystem() { return m_physicsSystem; }

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
			Window m_window;
			/** Rendering system */
			Renderer m_renderer;

			/** Input processing system */
			InputSystem m_inputSystem;
			/** Physics handling system */
			PhysicsSystem m_physicsSystem;
	};
}
