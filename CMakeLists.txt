cmake_minimum_required(VERSION 3.28)
project(Pathtracer)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(Libs/lodepng)

add_executable(Pathtracer src/main.cpp src/Image.h src/Math/Vector3.h
        src/Math/Ray.h
        src/Objects/Camera.h)

target_link_libraries(Pathtracer lodepng)