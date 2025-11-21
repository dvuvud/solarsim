#pragma once

#include <simulation/simulation.hpp>

namespace solarsim {
	class SimulationManager {
		public:
			static Simulation& getActiveSimulation() {
				static Simulation activeSimulation;
				return activeSimulation;
			}
		private:
			SimulationManager() {}
			~SimulationManager() {}
	};
}
