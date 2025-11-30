#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <typeindex>
#include <memory>
#include "entity.hpp"

namespace solarsim {

	/**
	 * @brief Manages entities and their components in the ECS
	 */
	class Registry {
		public:
			/**
			 * @brief Create a new entity
			 * @return Entity The newly created entity ID
			 */
			[[nodiscard]] Entity createEntity() {
				Entity e = nextEntity++;
				entities.insert(e);
				return e;
			}

			/**
			 * @brief Add a component to an entity
			 * @tparam Component Type of component to add
			 * @param e Entity to add the component to
			 * @param c Component instance to add
			 * 
			 * @note Overwrites existing component of same type
			 * @warning Entity must exist (created via createEntity())
			 */
			template<typename Component>
				void addComponent(Entity e, Component c) {
					getComponentStorage<Component>()[e] = c;
				}

			/**
			 * @brief Get a component from an entity
			 * @tparam Component Type of component to retrieve
			 * @param e Entity to get the component from
			 * @return Component& Reference to the component
			 * 
			 * @throws std::out_of_range if entity doesn't have the component
			 */
			template<typename Component>
				Component& getComponent(Entity e) {
					return getComponentStorage<Component>().at(e);
				}

			/**
			 * @brief Check if an entity has a specific component
			 * @tparam Component Type of component to check for
			 * @param e Entity to check
			 * @return bool True if entity has the component
			 */
			template<typename Component>
				bool hasComponent(Entity e) {
					auto& storage = getComponentStorage<Component>();
					return storage.find(e) != storage.end();
				}

			/**
			 * @brief Get all entities that have all specified components
			 * @tparam Components Component types to filter by
			 * @return std::vector<Entity> Entities matching the component filter
			 */
			template<typename... Components>
				[[nodiscard]] std::vector<Entity> view() {
					std::vector<Entity> result;
					if constexpr (sizeof...(Components) == 0) return result;

					auto& firstStorage = getComponentStorage<std::tuple_element_t<0, std::tuple<Components...>>>();

					for (auto& [entity, comp] : firstStorage) {
						bool hasAll = (hasComponent<Components>(entity) && ...);
						if (hasAll) result.push_back(entity);
					}

					return result;
				}

			/**
			 * Get all entities currently in scene
			 * @return std::unordered_seet<Entity> A set of all entities
			 */
			const auto& getEntities() const { return entities; }

		private:
			/** Set of all active entities */
			std::unordered_set<Entity> entities;
			/** Next available entity ID */
			uint32_t nextEntity = 0;

			/**
			 * @brief Base interface for type-erased component storage
			 */
			struct IComponentStorage {
				virtual ~IComponentStorage() = default;
			};

			/**
			 * @brief Typed component storage for a specific component type
			 * @tparam Component The component type to store
			 */
			template<typename Component>
				struct ComponentStorage : IComponentStorage {
					/** Entity-to-component map */
					std::unordered_map<Entity, Component> components;
				};

			/** Type-indexed component storage */
			std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;

			/**
			 * @brief Get or create the storage for a component type
			 * @tparam Component Component type to get storage for
			 * @return std::unordered_map<Entity, Component>& Reference to the component storage
			 * 
			 * @note Creates storage on first access for a component type
			 */
			template<typename Component>
				std::unordered_map<Entity, Component>& getComponentStorage() {
					auto typeIndex = std::type_index(typeid(Component));
					auto it = componentStorages.find(typeIndex);
					if (it == componentStorages.end()) {
						auto storage = std::make_unique<ComponentStorage<Component>>();
						auto& components = storage->components;
						componentStorages[typeIndex] = std::move(storage);
						return components;
					}
					return static_cast<ComponentStorage<Component>*>(it->second.get())->components;
				}
	};
}
