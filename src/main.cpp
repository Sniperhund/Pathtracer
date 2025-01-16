#include <iostream>
#include <cstdlib>
#include <chrono>

#include "Math/Vector3.h"
#include "Objects/HitRecord.h"
#include "Objects/Scene.h"
#include "Math/Utility.h"
#include "Objects/Sphere.h"
#include "Pathtracer.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

int main() {
    Pathtracer pathtracer;

    pathtracer.Resize(1280, 720);
    pathtracer.samplesPerPixel = 512;
    pathtracer.maxDepth = 32;
    pathtracer.threadCount = std::thread::hardware_concurrency() - 4;
    pathtracer.batchSize = 32;
    pathtracer.antialias = true;

    std::shared_ptr<Scene> scene = pathtracer.GetScene();

    // Ground
    scene->AddObject(std::make_shared<Sphere>(Vector3(0, -1000, -1), 1000,
                                              std::make_shared<Metal>(Vector3(0.5f, 0.5f, 0.5f), 0.3f)));

    scene->AddObject(std::make_shared<Sphere>(Vector3(0, 1, 0), 1,
                                              std::make_shared<Metal>(Vector3(0.9f, 0.3f, 0.6f), 0.1f)));

    std::shared_ptr<Camera> camera = pathtracer.GetCamera();
    camera->origin = Vector3(13, 2, 3);
    camera->lookAt = Vector3(0, 0, 0);
    camera->vfov = 25;
    camera->defocusAngle = 1;
    camera->focusDist = 13.0f;

    scene->BuildBVH();

    auto start = std::chrono::high_resolution_clock::now();

    pathtracer.Render("../output.png");

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) - duration_seconds;
    std::cout << "It took " << duration_seconds.count() << "," << duration_milliseconds.count() << " s" << std::endl;

    return 0;
}
