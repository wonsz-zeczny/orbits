add_library(vendor-libs STATIC 
    glad/src/gl.c
    stb/stb_image.cpp)

target_include_directories(vendor-libs PUBLIC glad/include)
target_include_directories(vendor-libs PUBLIC stb) 