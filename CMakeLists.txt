cmake_minimum_required(VERSION 3.10)
project(SolarSim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

enable_language(C)
enable_language(CXX)

add_library(glad_c STATIC lib/glad/src/glad.c)
target_include_directories(glad_c PUBLIC lib/glad/include)

add_subdirectory(lib/glfw)
find_package(OpenGL REQUIRED)

add_executable(solarsim 
    src/main.cpp
)

target_link_libraries(solarsim
    glfw
    glad_c
    OpenGL::GL
)

target_include_directories(solarsim PRIVATE 
    include
    lib/glfw/include
)
