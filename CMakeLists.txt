include(FetchContent)

cmake_minimum_required(VERSION 3.24)

project(orbits)

add_compile_options("/std:c++latest")

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw)

add_subdirectory(vendor)

add_executable(app main.cpp)

include_directories(${glfw_SOURCE_DIR}/include)

target_link_libraries(app PUBLIC glad glfw)