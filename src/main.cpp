#include <iostream>
#include <cstdlib>
#include "Image.h"
#include "Objects/Camera.h"
#include "Math/Vector3.h"
#include "Objects/HitRecord.h"
#include "Objects/Scene.h"
#include "Math/Utility.h"
#include "Objects/Sphere.h"
#include "Pathtracer.h"

int main() {
    GlobalSettings::width = 1920;
    GlobalSettings::height = 1080;
    GlobalSettings::samplesPerPixel = 10;

    Pathtracer pathtracer;

    std::shared_ptr<Scene> scene = pathtracer.GetScene();

    scene->AddObject(std::make_shared<Sphere>(Vector3(0, 0, -1), 0.5f));
    scene->AddObject(std::make_shared<Sphere>(Vector3(0, -100.5f, -1), 100));

    std::shared_ptr<Camera> camera = pathtracer.GetCamera();
    camera->origin = Vector3();
    camera->focalLength = 1.0f;

    pathtracer.Render("../output.png");

    return 0;
}
