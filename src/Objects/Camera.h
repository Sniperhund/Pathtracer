//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include <memory>
#include "../Math/Vector3.h"
#include "../Math/Ray.h"
#include "Material/Material.h"
#include "Scene.h"
#include "../Math/Utility.h"

class Camera {
public:
    Vector3 origin = Vector3(), lookAt = Vector3();
    float vfov = 45, defocusAngle = 0, focusDist = 10;
    bool antialias = true;

    Camera(Vector3 origin, Vector3 lookAt, float focalLength, float vfov)
            : origin(origin), lookAt(lookAt), vfov(vfov) {}

    Camera() {}

    void CalculateValues(int width, int height) {
        float theta = DegreesToRadians(vfov);
        float h = tanf(theta / 2);
        m_viewportHeight = 2 * h * focusDist;
        m_viewportWidth = m_viewportHeight * ((float)width / (float)height);

        m_w = Normalize(origin - lookAt);
        m_u = Normalize(Cross(Vector3(0, 1, 0), m_w));
        m_v = Cross(m_w, m_u);

        m_viewportU = m_viewportWidth * m_u;
        m_viewportV = m_viewportHeight * -m_v;

        m_pixelDeltaU = m_viewportU / (float)width;
        m_pixelDeltaV = m_viewportV / (float)height;

        m_viewportUpperLeft = origin - (focusDist * m_w) - m_viewportU / 2 - m_viewportV / 2;
        m_pixel00Loc = m_viewportUpperLeft + 0.5f * (m_pixelDeltaU + m_pixelDeltaV);

        float defocusRadius = focusDist * tanf(DegreesToRadians(defocusAngle / 2));
        m_defocusDiskU = m_u * defocusRadius;
        m_defocusDiskV = m_v * defocusRadius;
    }

    Ray GetRay(int x, int y) {
        Vector3 offset;

        if (antialias)
            offset = SampleSquare();

        Vector3 pixelSample = m_pixel00Loc + (((float)x + offset.x) * m_pixelDeltaU) + (((float)y + offset.y) * m_pixelDeltaV);

        Vector3 rayOrigin = (defocusAngle <= 0) ? origin : DefocusDiskSample();
        Vector3 rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    Vector3 RayColor(const Scene& scene, const Ray& ray, int depth) {
        if (depth <= 0)
            return Vector3(0);

        HitRecord hit;
        if (scene.Hit(ray, 0.001f, infinity, hit)) {
            Ray scattered;
            Vector3 attenuation;
            if (hit.material->Scatter(ray, hit, attenuation, scattered))
                return attenuation * RayColor(scene, scattered, depth - 1);
            return Vector3(0);
        }

        Vector3 unitDirection = Normalize(ray.direction);
        float a = 0.5f * (unitDirection.y + 1.0f);
        return (1.0f - a) * Vector3(1) + a * Vector3(0.5f, 0.7f, 1.0f);
    }

private:
    Vector3 SampleSquare() const {
        return Vector3(RandomFloat() - 0.5f, RandomFloat() - 0.5f, 0);
    }

    Vector3 DefocusDiskSample() const {
        Vector3 p = RandomInUnitDisk();
        return origin + (p.x * m_defocusDiskU) + (p.y * m_defocusDiskV);
    }

    float m_viewportHeight, m_viewportWidth;
    Vector3 m_viewportU, m_viewportV, m_pixelDeltaU, m_pixelDeltaV, m_viewportUpperLeft, m_pixel00Loc, m_u, m_v, m_w, m_defocusDiskU, m_defocusDiskV;
};
