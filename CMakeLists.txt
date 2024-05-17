cmake_minimum_required(VERSION 3.28)
project(Pathtracer)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(Libs/lodepng)

add_library(Pathtracer src/Image.h src/Math/Vector3.h
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
        src/Material/Material.h
        src/Material/Lambertian.h
        src/Material/Metal.h
        src/Material/Dielectric.h
        src/Objects/AABB.h
        src/Objects/BVHNode.h
)

target_link_libraries(Pathtracer lodepng)
target_include_directories(Pathtracer PUBLIC ./src)

project(Pathtracer-exe)

add_executable(Pathtracer-exe src/main.cpp)

target_link_libraries(Pathtracer-exe Pathtracer)