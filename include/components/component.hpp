#pragma once

namespace solarsim {
	class Entity;
	class Component {
		public:
			Entity* m_owner;
			bool m_isActive;
			Component();
			virtual ~Component();
			virtual void Update(float deltaTime);
	};
}
