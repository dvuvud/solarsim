# Engine Architecture

This document describes the structure and dependencies of the engine.

---

## Engine Components

### 1. Window
- **Members:**
  - `GLFWwindow* handle`
  - `width, height, title`
- **Methods:**
  - `init()`
  - `shouldClose()`
  - `pollEvents()`
  - `swapBuffers()`
- **Responsibility:** Handles window creation, context, and event polling.

---

### 2. Renderer
- **Members:**
  - `Camera* activeCamera` (reference only)
  - References `Simulation` (read-only)
  - Shaders (loaded once / cached)
  - Materials (owned or shared)
  - Meshes (GPU-side cache)
- **Methods:**
  - `render(const Simulation&, const Camera&)`
    - For each `Entity`:
      1. Draw mesh with its material
      2. Set shader uniforms
      3. Make OpenGL draw calls
- **Responsibility:** All rendering, batching, shader bindings.

---

### 3. Simulation
- **Members:**
  - `std::vector<std::unique_ptr<Entity>> entities`
  - `Camera camera`
- **Methods:**
  - `update(float dt)` → calls `Entity::update(dt)`
  - `spawnEntity(...)`
  - `getEntities()`
- **Responsibility:** World state and entity lifecycle.

---

### 4. InputManager
- **Members:**
  - `Window* window` (to access GLFW input)
  - `Camera* camera` (to move the view)
- **Methods:**
  - `processInput(float dt)`:
    - Reads GLFW keys/mouse from window
    - Updates camera position/rotation
- **Responsibility:** Abstracting input logic.

---

### 5. Optional Future Systems
- **AudioSystem:** handles 3D sounds (OpenAL / FMOD)
- **PhysicsSystem:** updates positions, collisions, communicates with Simulation
- **UISystem:** handles in-game UI, may draw via Renderer
- **ResourceManager:** loads/caches textures, meshes, shaders

---

## Engine Main Loop

### `init()`
- `glfwInit()`
- `window.init()`
- `simulation = std::make_unique<Simulation>()`
- `renderer = std::make_unique<Renderer>()`
- `inputManager = std::make_unique<InputManager>(&window, simulation->getCamera())`

### `run()`
- `while (!window.shouldClose()):`
- `inputManager->processInput(dt)`
- `simulation->update(dt)`
- `renderer->render(*simulation, simulation->getCamera())`
- `window.swapBuffers()`
- `window.pollEvents()`
- `cleanup()`

---

## Dependencies

### Entity
- **Members:**
  - `Transform transform` (position, rotation, scale, `getModelMatrix()`)
  - `Mesh* mesh`
  - `Material* material`
- **Methods:**
  - `update(float dt)`
  - `render(Shader& shader)`
- **Responsibility:** Represents one visible or simulated object.

### Material
- **Members:** `Shader* shader`, `glm::vec3 color`, `float shininess`, `Texture* texture`
- **Methods:** `bind()`, `setUniforms()`
- **Responsibility:** Stores rendering state per object.

### Mesh
- **Members:** `std::vector<Vertex> vertices`, `std::vector<unsigned int> indices`, `GLuint VAO, VBO, EBO`
- **Methods:** `uploadToGPU()`, `draw()`
- **Responsibility:** Vertex data and OpenGL buffer management.

### Camera
- **Members:** `glm::vec3 position, front, up`, `float fov, nearPlane, farPlane`
- **Methods:** `getViewMatrix()`, `getProjectionMatrix()`
- **Responsibility:** Defines viewpoint and projection.

---

## Frame Flow
# Frame Update Flow

 This section describes the order of operations for each frame in the engine’s main loop.

 ---

## Main Loop Overview

 Every frame, the **Engine** coordinates input, simulation, and rendering in this order:

 1. **Process Input**
 - **Call:** `InputManager.processInput()`
 - **Purpose:** Reads keyboard and mouse input from the `Window`.
 - **Effect:** Updates the `Camera`’s position and rotation.

 2. **Update Simulation**
 - **Call:** `Simulation.update()`
 - **Purpose:** Updates all `Entity` objects.
 - **Effect:** Handles logic, movement, and state changes for entities.

 3. **Render Scene**
 - **Call:** `Renderer.render(Simulation, Camera)`
 - **Purpose:** Draws all entities to the screen.
 - **Steps:**
 1. For each `Entity` in the `Simulation`:
 - Retrieve the **Mesh** and **Material**.
 - Bind the **Material**’s **Shader**.
 - Set shader uniforms:
 - `model` — entity’s transform matrix
 - `view` — from the `Camera`
 - `projection` — from the `Camera`
 - Issue draw call (e.g., `glDrawElements()`).

 4. **Window Management**
 - **Swap Buffers:** Displays the rendered frame.
 - **Poll Events:** Processes user input and OS events.

 ---

## Notes

 - The **Camera** provides both `getViewMatrix()` and `getProjectionMatrix()`, since it stores FOV, aspect ratio, and render distance.
 - The **Renderer** does **not** own entities — it just draws whatever the `Simulation` provides.
 - The **update order (Input → Update → Render → Swap Buffers)** follows the standard game loop used by most engines (Unreal, Unity, Godot, etc.).

 ---
