#pragma once

#include <mesh/mesh.hpp>
#include <components/transform_component.hpp>
#include <memory>

namespace solarsim {
	class Entity {
		public:
			std::vector<Component*> m_components;
			TransformComponent* m_transform;
			template <typename T, typename... Args>
				T* AddComponent(Args&&... args) {
					T* newComponent = new T(std::forward<Args>(args)...);
					newComponent->Owner = this;
					m_components.push_back(newComponent);
					return newComponent;
				}
			virtual ~Entity() = default;
			virtual void update(float deltaTime) {
				for (Component* c : m_components)
					if (c->m_isActive) c->Update(deltaTime);
			}
	};
}
