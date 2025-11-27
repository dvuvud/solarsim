# SolarSim

I built this to learn OpenGL, and somewhere between the shader errors and matrix math, I ended up with something that actually looks like space.

## Demo of the solar system

![ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/f9938905-46cb-466a-a438-b673e3769ecf)

## Build & Run

### Required System Libraries
- [OpenGL](https://www.opengl.org/) (3.3+)
- [CMake](https://cmake.org/download/) (3.10+)
- C++20 compiler ([reference](https://en.cppreference.com/w/cpp/compiler_support/20.html))
- [GNU Make](https://www.gnu.org/software/make/) (optional if using CMake directly)

### Included Dependencies (No installation needed)
The following are included as submodules or source code:
- [GLFW](https://github.com/glfw/glfw) - Window and input management
- [GLM](https://github.com/g-truc/glm) - 3D mathematics library  
- [GLAD](https://glad.dav1d.de/) - OpenGL function loader
- [stb_image](https://github.com/nothings/stb) - Image loading library
- [googletest](https://github.com/google/googletest) - C++ testing framework
- [assimp](https://github.com/assimp/assimp) - Asset loading library
- [Dear ImGui](https://github.com/ocornut/imgui/tree/docking) - C++ GUI library

### Commands

#### Using Makefile (Recommended)
```bash
# Clone with submodules
git clone --recursive https://github.com/dvuvud/solarsim.git
cd solarsim

# Build and run using the provided Makefile
make build
make run

# Or build and run in one command
make all

# Clean build artifacts
make clean
```
#### Using CMake Directly
```bash
# Clone with submodules
git clone --recursive https://github.com/dvuvud/solarsim.git
cd solarsim

# Configure and build
cmake -B build
cmake --build build --target solarsim

# Run the application
./build/solarsim # Linux/macOS
build\Debug\solarsim.exe # Windows
```

## Controls / Keybinds

| Key           | Action                                      |
|---------------|---------------------------------------------|
| `W`           | Move camera forward                         |
| `S`           | Move camera backward                        |
| `A`           | Move camera left                            |
| `D`           | Move camera right                           |
| `Space`       | Move camera up                              |
| `Left Shift`  | Move camera down                            |
| `R`           | Toggle time reversal (rewind / forward)     |
| `P`           | Toggle pause / unpause                      |
| `G`           | Toggle grid                                 |
| `Tab`         | Toggle mouse capture / release              |
| `Scroll`      | Zoom in & out                               |
| `Escape`      | Quit application                            |
