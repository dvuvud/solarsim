#pragma once

namespace solarsim {
	class PhysicsSystem {
		public:
			void update(float deltaTime);
		private:
			float timeScale = 1.0f;
			const float G = 10.0f;
			const float SOFTENING_SQUARED = 1.0f;
	};
}
