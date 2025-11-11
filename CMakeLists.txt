cmake_minimum_required(VERSION 3.10)

if(UNIX)
    cmake_policy(SET CMP0072 NEW)
    set(OpenGL_GL_PREFERENCE GLVND)
endif()

project(SolarSim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(glad_c STATIC lib/glad/src/glad.c)
target_include_directories(glad_c PUBLIC lib/glad/include)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

find_package(OpenGL REQUIRED)

add_executable(solarsim 
	src/main.cpp
	src/engine/engine.cpp
	src/core/window.cpp
	src/core/input_manager.cpp
	src/graphics/shader.cpp
	src/graphics/texture.cpp
	src/graphics/camera.cpp
	src/graphics/renderer.cpp
	src/simulation/simulation.cpp
	src/simulation/planet.cpp
	src/mesh/mesh.cpp
	src/mesh/cube.cpp
)

if(APPLE)
    target_compile_options(solarsim PRIVATE -Wno-deprecated-declarations)
endif()

target_link_libraries(solarsim
	glfw
	glm
	glad_c
	OpenGL::GL
)

target_include_directories(solarsim PRIVATE
	include
	lib/stb
)
