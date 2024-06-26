include(FetchContent)

cmake_minimum_required(VERSION 3.22)

project(orbits)


if(${MSVC})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20") 
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set(SHADERS_DIR "${CMAKE_SOURCE_DIR}/shaders/")
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources/")

configure_file("${CMAKE_SOURCE_DIR}/include/Utils.hpp.in" "${CMAKE_SOURCE_DIR}/include/Utils.hpp") 

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

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(glfw glm spdlog json) 

add_subdirectory(vendor)

add_subdirectory(src)

add_executable(app main.cpp)

target_link_libraries(app PUBLIC orbits-lib) 