# SolarSim

I built this to learn OpenGL, and somewhere between the shader errors and matrix math, I ended up with something that actually looks like space.

## Build & Run

### Required System Libraries
- **OpenGL** (3.3+)
- **CMake** (3.10+)
- **C++20 compiler**
- **Make** (for the Makefile commands)

### Included Dependencies (No installation needed)
The following are included as submodules or source code:
- **GLFW** - Window and input management
- **GLM** - 3D mathematics library  
- **GLAD** - OpenGL function loader
- **stb_image** - Image loading library

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
