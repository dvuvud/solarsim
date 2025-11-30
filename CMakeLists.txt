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
find_package(X11 REQUIRED)

## Library for core functionality
add_library(solarsim_core
	src/engine/engine.cpp
	src/engine/renderer.cpp
	src/engine/window.cpp
	src/managers/asset_manager.cpp
	src/managers/scene_manager.cpp
	src/systems/input_system.cpp
	src/systems/physics_system.cpp
	lib/imgui/imgui.cpp
	lib/imgui/imgui_draw.cpp
	lib/imgui/imgui_tables.cpp
	lib/imgui/imgui_widgets.cpp
	lib/imgui/imgui_demo.cpp
	lib/imgui/backends/imgui_impl_opengl3.cpp
	lib/imgui/backends/imgui_impl_glfw.cpp
)

target_include_directories(solarsim_core PUBLIC
	include
	lib/stb
	lib/imgui
	lib/imgui/backends
)

target_link_libraries(solarsim_core
	glfw
	glm
	glad_c
	OpenGL::GL
	X11::X11
)

if(APPLE)
	target_compile_options(solarsim_core PRIVATE -Wno-deprecated-declarations)
endif()


## Main executable
add_executable(solarsim src/app.cpp)
target_link_libraries(solarsim solarsim_core)


###########################################################
#			Tests				  #
###########################################################

enable_testing()
add_subdirectory(lib/googletest)

add_executable(solarsim_tests test/
	test/scene/registry_test.cpp
	test/scene/scene_test.cpp
	test/components/transform_component_test.cpp
	test/components/component_integration_test.cpp
	test/components/renderer_components_test.cpp
	test/systems/physics_system_test.cpp
	test/systems/input_system_test.cpp
	test/managers/scene_manager_test.cpp
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
