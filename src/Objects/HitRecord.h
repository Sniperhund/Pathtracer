//
// Created by Lucas on 14-05-2024.
//

#pragma once

#include "../Math/Vector3.h"
#include "../Math/Ray.h"

struct Material;

struct HitRecord {
    Vector3 origin;
    Vector3 normal;
    std::shared_ptr<Material> material;
    float t;
    bool frontFace;

    void SetFaceNormal(const Ray& ray, const Vector3& outwardNormal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        frontFace = Dot(ray.direction, outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
