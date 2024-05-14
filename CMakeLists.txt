cmake_minimum_required(VERSION 3.28)
project(Pathtracer)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(Libs/lodepng)

add_executable(Pathtracer src/main.cpp src/Image.h src/Math/Vector3.h
        src/Math/Ray.h
        src/Objects/Camera.h
        src/Objects/Object.h
        src/Objects/HitRecord.h
        src/Objects/Sphere.h
        src/Objects/Scene.h
        src/Math/Utility.h
        src/Pathtracer.h
        src/GlobalSettings.cpp
        src/GlobalSettings.h
)

target_link_libraries(Pathtracer lodepng)