#pragma once

namespace solarsim {
	class PhysicsSystem {
		public:
			void update(float deltaTime);
		private:
			const float G = 2.0f;
			const float SOFTENING_SQUARED = 1.0f;
	};
}
