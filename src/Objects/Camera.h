//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include <memory>
#include "../Math/Vector3.h"
#include "../Math/Ray.h"
#include "Scene.h"
#include "../Math/Utility.h"
#include "../GlobalSettings.h"

class Camera {
public:
    Vector3 origin;
    float focalLength;

    Camera(Vector3 origin, float focalLength, float samplesPerPixel)
            : origin(origin), focalLength(focalLength) {}

    Camera() {
        Camera(Vector3(), 1, 1);
    }

    void CalculateValues() {
        m_viewportHeight = 2.0f;
        m_viewportWidth = m_viewportHeight * ((float)GlobalSettings::width / (float)GlobalSettings::height);

        m_viewportU = Vector3(m_viewportWidth, 0, 0);
        m_viewportV = Vector3(0, -m_viewportHeight, 0);

        m_pixelDeltaU = m_viewportU / (float)GlobalSettings::width;
        m_pixelDeltaV = m_viewportV / (float)GlobalSettings::height;

        m_viewportUpperLeft = origin - Vector3(0, 0, focalLength) - m_viewportU / 2 - m_viewportV / 2;
        m_pixel00Loc = m_viewportUpperLeft + 0.5f * (m_pixelDeltaU + m_pixelDeltaV);
    }

    Ray GetRay(int x, int y) {
        Vector3 offset = SampleSquare();
        Vector3 pixelSample = m_pixel00Loc + (((float)x + offset.x) * m_pixelDeltaU) + (((float)y + offset.y) * m_pixelDeltaV);

        Vector3 rayDirection = pixelSample - origin;

        return Ray(origin, rayDirection);
    }

    Vector3 RayColor(int x, int y, const Scene& scene, const Ray& ray) {
        HitRecord hit;
        if (scene.Hit(ray, 0, infinity, hit)) {
            return 0.5f * (hit.normal + Vector3(1));
        }

        Vector3 unitDirection = Normalize(ray.direction);
        float a = 0.5f * (unitDirection.y + 1.0f);
        return (1.0f - a) * Vector3(1) + a * Vector3(0.5f, 0.7f, 1.0f);
    }

private:
    Vector3 SampleSquare() const {
        return Vector3(RandomFloat() - 0.5f, RandomFloat() - 0.5f, 0);
    }

    float m_viewportHeight, m_viewportWidth;
    Vector3 m_viewportU, m_viewportV, m_pixelDeltaU, m_pixelDeltaV, m_viewportUpperLeft, m_pixel00Loc;
};
