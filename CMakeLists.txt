cmake_minimum_required(VERSION 3.10)

if(UNIX)
	cmake_policy(SET CMP0072 NEW)
	set(OpenGL_GL_PREFERENCE GLVND)
endif()

project(SolarSim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(glad_c STATIC lib/glad/src/glad.c)
target_include_directories(glad_c PUBLIC lib/glad/include)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)

find_package(OpenGL REQUIRED)


## Library for core functionality
add_library(solarsim_core
	src/engine/engine.cpp
	src/core/window.cpp
	src/core/input_manager.cpp
	src/graphics/shader.cpp
	src/graphics/texture.cpp
	src/graphics/camera.cpp
	src/graphics/renderer.cpp
	src/graphics/grid.cpp
	src/simulation/simulation.cpp
	src/simulation/planet.cpp
	src/simulation/sun.cpp
	src/mesh/mesh.cpp
	src/mesh/cube.cpp
)

target_include_directories(solarsim_core PUBLIC
	include
	lib/stb
)

target_link_libraries(solarsim_core
	glfw
	glm
	glad_c
	OpenGL::GL
)

if(APPLE)
	target_compile_options(solarsim_core PRIVATE -Wno-deprecated-declarations)
endif()


## Main executable
add_executable(solarsim src/main.cpp)
target_link_libraries(solarsim solarsim_core)


###########################################################
#			Tests				  #
###########################################################

enable_testing()
add_subdirectory(vendor/googletest)

add_executable(solarsim_tests
	test/simulation/test_entity.cpp
	test/simulation/test_planet.cpp
)

target_link_libraries(solarsim_tests
	solarsim_core
	gtest
	gtest_main
)

target_include_directories(solarsim_tests PRIVATE
	include
)

include(GoogleTest)
gtest_discover_tests(solarsim_tests)
