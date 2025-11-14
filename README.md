# SolarSim

I built this to learn OpenGL, and somewhere between the shader errors and matrix math, I ended up with something that actually looks like space.

## Build & Run

### Required System Libraries
- **OpenGL** (3.3+)
- **CMake** (3.10+)
- **C++20 compiler**

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
