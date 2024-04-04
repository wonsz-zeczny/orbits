add_library(orbits-lib
    Debug.cpp
    Camera.cpp
)

target_include_directories(orbits-lib PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(orbits-lib PUBLIC glad glfw glm spdlog)