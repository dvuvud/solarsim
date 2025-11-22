#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include "entity.hpp"

namespace solarsim {
	class Registry {
		public:
			Entity createEntity() {
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
				bool hasComponent(Entity e) const {
					auto& storage = getComponentStorage<Component>();
					return storage.find(e) != storage.end();
				}

			template<typename... Components>
				std::vector<Entity> view() const {
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
			unsigned int nextEntity = 0;

			// Each component type gets its own static storage
			template<typename Component>
				std::unordered_map<Entity, Component>& getComponentStorage() {
					static std::unordered_map<Entity, Component> storage;
					return storage;
				}
	};

}
