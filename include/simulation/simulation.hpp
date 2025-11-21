#pragma once

#include <graphics/camera.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace solarsim {
	class LightComponent;
	class MeshComponent;
	class Entity;
	class Simulation {
		public:
			Simulation();
			~Simulation();

			void RegisterEntity(const std::string& type, std::unique_ptr<Entity> p_entity);

			void update(float deltaTime);

			void clearAllEntities();
			
			Camera* getCamera() { return m_camera.get(); }
			const Camera* getCamera() const { return m_camera.get(); }

			const std::vector<std::unique_ptr<Entity>>* getType(const std::string& type) const { 
				auto it = EntityByType.find(type); 
				if (it != EntityByType.end()) {
					return &it->second;
				}
				return nullptr;
			}

			void toggleReverse() { isReversing = !isReversing; }
			void togglePause() { isPausing = !isPausing; }
			void setCameraAspectRatio(float ar) { if (m_camera) m_camera->setAspectRatio(ar); }
		private:
			std::unordered_map<std::string, std::vector<std::unique_ptr<Entity>>> EntityByType;
			std::unique_ptr<Camera> m_camera;

			bool isReversing = false;
			bool isPausing = false;

			// Gravity constants
			const float G = 5.0f;
			const float SOFTENING_SQUARED = 100.0f;
	};
}
