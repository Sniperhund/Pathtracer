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
    GlobalSettings::width = 1920;
    GlobalSettings::height = 1080;
    GlobalSettings::samplesPerPixel = 1024;
    GlobalSettings::maxDepth = 10;
    GlobalSettings::antialias = true;

    Pathtracer pathtracer;

    std::shared_ptr<Scene> scene = pathtracer.GetScene();

    // Ground
    scene->AddObject(std::make_shared<Sphere>(Vector3(0, -1000, -1), 1000,
                                              std::make_shared<Lambertian>(Vector3(0.5f, 0.5f, 0.5f))));

    for (int x = -11; x < 11; x++) {
        for (int y = -11; y < 11; y++) {
            float chooseMat = RandomFloat();
            float radius = RandomFloat(0.1f, 0.3f);
            Vector3 origin(x + 0.9f * RandomFloat(), radius, y + 0.9f * RandomFloat());

            if ((origin - Vector3(4, 0.2f, 0)).Length() > 0.9f) {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8f) {
                    Vector3 albedo = Vector3::Random() * Vector3::Random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    scene->AddObject(std::make_shared<Sphere>(origin, radius, sphereMaterial));
                } else if (chooseMat < 0.95f) {
                    Vector3 albedo = Vector3::Random(0.5f, 1);
                    float roughness = RandomFloat(0, 0.5f);
                    sphereMaterial = std::make_shared<Metal>(albedo, roughness);
                    scene->AddObject(std::make_shared<Sphere>(origin, radius, sphereMaterial));
                } else {
                    sphereMaterial = std::make_shared<Dielectric>(1.5f);
                    scene->AddObject(std::make_shared<Sphere>(origin, radius, sphereMaterial));
                }
            }
        }
    }

    scene->AddObject(std::make_shared<Sphere>(Vector3(0, 1, 0), 1,
                                              std::make_shared<Lambertian>(Vector3(0.1f, 0.2f, 0.5f))));
    scene->AddObject(std::make_shared<Sphere>(Vector3(-4, 1, 0), 1,
                                              std::make_shared<Metal>(Vector3(0.8f, 0.6f, 0.2f), 0.3f)));
    scene->AddObject(std::make_shared<Sphere>(Vector3(4, 1, 0), 1,
                                              std::make_shared<Dielectric>(1.0f / 1.33f)));

    std::shared_ptr<Camera> camera = pathtracer.GetCamera();
    camera->origin = Vector3(13, 2, 3);
    camera->lookAt = Vector3(0, 0, 0);
    camera->vfov = 25;
    camera->defocusAngle = 0.6f;
    camera->focusDist = 10.0f;

    auto start = std::chrono::high_resolution_clock::now();

    pathtracer.Render("../output.png");

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration_seconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) - duration_seconds;
    std::cout << "It took " << duration_seconds.count() << "," << duration_milliseconds.count() << " s" << std::endl;

    return 0;
}
