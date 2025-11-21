#pragma once

#include <memory>

namespace solarsim {
	class Window;
	class Renderer;
	class InputManager;
	class Engine {
		public:
			static Engine* Current() { return current; }
			void SetCurrent() { current = this; }

			const Window* activeWindow() const { return m_window; }

			Engine();
			~Engine();
			void run();
		private:
			static Engine* current;
			Window* m_window;
			Renderer* m_renderer;
			InputManager* m_inputManager;
	};
}
