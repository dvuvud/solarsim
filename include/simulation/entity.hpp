#pragma once

#include <mesh/mesh.hpp>
#include <components/transform_component.hpp>
#include <managers/simulation_manager.hpp>
#include <memory>

namespace solarsim {
	class Entity {
		public:
			TransformComponent* m_transform;
			virtual ~Entity() = default;
			virtual void update(float deltaTime);
	};
}
