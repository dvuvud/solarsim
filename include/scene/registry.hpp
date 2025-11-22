#pragma once

#include <unordered_map>
#include <unordered_set>
#include "entity.hpp"

namespace solarsim {
	class Registry {
		public:
			Entity createEntity();

			template<typename Component>
				void addComponent(Entity e, Component c) {
					getComponentStorage<Component>()[e] = c;
				}

			template<typename Component>
				Component& getComponent(Entity e) {
					return getComponentStorage<Component>()[e];
				}

			template<typename... Components>
				std::vector<Entity> view() {
					
				}
					

		private:
			std::unordered_set<Entity> entities;

			template<typename Component>
				std::unordered_map<Entity, Component>& getComponentStorage();
	};
}
