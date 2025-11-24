#pragma once

namespace solarsim {
	class PhysicsSystem {
		public:
			void update(float deltaTime);
		private:
			float timeScale = 1.0f;
			const float G = 7.5f;
			const float SOFTENING_SQUARED = 2.0f;
	};
}
