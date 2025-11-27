#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <typeindex>
#include <memory>
#include "entity.hpp"

namespace solarsim {
	class Registry {
		public:
			[[nodiscard]] Entity createEntity() {
				Entity e = nextEntity++;
				entities.insert(e);
				return e;
			}

			template<typename Component>
				void addComponent(Entity e, Component c) {
					getComponentStorage<Component>()[e] = c;
				}

			template<typename Component>
				Component& getComponent(Entity e) {
					return getComponentStorage<Component>().at(e);
				}

			template<typename Component>
				bool hasComponent(Entity e) {
					auto& storage = getComponentStorage<Component>();
					return storage.find(e) != storage.end();
				}

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
		private:
			std::unordered_set<Entity> entities;
			uint32_t nextEntity = 0;

			struct IComponentStorage {
				virtual ~IComponentStorage() = default;
			};

			template<typename Component>
				struct ComponentStorage : IComponentStorage {
					std::unordered_map<Entity, Component> components;
				};

			std::unordered_map<std::type_index, std::unique_ptr<IComponentStorage>> componentStorages;

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
