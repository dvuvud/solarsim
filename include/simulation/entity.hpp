#pragma once

#include <mesh/mesh.hpp>
#include <components/transform_component.hpp>
#include <memory>

namespace solarsim {
	class LightComponent;
	class Entity {
		public:
			std::vector<Component*> m_components;
			TransformComponent* m_transform;
			template <typename T, typename... Args>
				T* AddComponent(Args&&... args) {
					T* newComponent = new T(std::forward<Args>(args)...);
					newComponent->Owner = this;
					m_components.push_back(newComponent);
					if constexpr (std::is_same<T, LightComponent>)
						SimulationManager::getActiveSimulation()->RegisterLight(this);
					if constexpr (std::is_same<T, MeshComponent>)
						SimulationManager::getActiveSimulation()->RegisterRenderable(this);
					return newComponent;
				}
			virtual ~Entity() = default;
			virtual void update(float deltaTime) {
				for (Component* c : m_components)
					if (c->m_isActive) c->Update(deltaTime);
			}
	};
}
