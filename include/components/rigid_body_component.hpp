#pragma once

#include "component.hpp"
#include "glm/vec3.hpp"

namespace solarsim {
	class Rigidbodycomponent : public Component {
		public:
			float m_mass;
			glm::vec3 m_vel;
			void applyForce(glm::vec3 vel);
	};
}

