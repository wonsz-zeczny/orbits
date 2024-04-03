include(FetchContent)

cmake_minimum_required(VERSION 3.22)

project(orbits)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.8
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.10.0
)

FetchContent_MakeAvailable(glfw spdlog)

add_subdirectory(vendor)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC glad glfw spdlog)