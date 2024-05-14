#include <iostream>
#include <cstdlib>
#include "Image.h"
#include "Objects/Camera.h"

Vector3 RayColor(const Ray& ray) {
    Vector3 unitDirection = Normalize(ray.direction);
    float a = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - a) * Vector3(1) + a * Vector3(0.5f, 0.7f, 1.0f);
}

int main() {
    int width = 1920, height = 1080;
    Image image = Image(width, height);

    Camera camera(Vector3(), 1.0f, (float)width, (float)height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Vector3 color = RayColor(camera.GetRay(x, y));

            image.SetPixel(x, y, color);
        }
    }

    image.Save("../output.png");

    return 0;
}
