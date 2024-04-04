include(FetchContent)

cmake_minimum_required(VERSION 3.22)

project(orbits)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git 
        GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(glfw glm spdlog)

add_subdirectory(vendor)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC glad glfw glm spdlog) 