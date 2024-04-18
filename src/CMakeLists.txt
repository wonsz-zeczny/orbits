add_library(orbits-lib
    Init.cpp
    Shader.cpp
    Program.cpp
    Texture.cpp
    Camera.cpp
    shapes/Sphere.cpp
    planetary-system/PlanetarySystem.cpp 
    planetary-system/CelestialBody.cpp) 

target_include_directories(orbits-lib PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(orbits-lib PUBLIC vendor-libs glfw glm spdlog)