# SolarSim

A solar system simulator that models celestial mechanics with real-time physics.

## Build & Run

### Required System Libraries
- **OpenGL** (3.3+) - Graphics API/Specification
- **CMake** (3.10+) - Build system
- **C++17 compiler** - GCC, Clang, or MSVC

### Included Dependencies (No installation needed)
The following are included as submodules or source code:
- **GLFW** - Window and input management
- **GLM** - 3D mathematics library  
- **GLAD** - OpenGL function loader
- **stb_image** - Image loading library

### Commands
```bash
git clone --recursive https://github.com/dvuvud/solarsim.git
cd solarsim
make build
make run
```
