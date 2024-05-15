//
// Created by Lucas on 15-05-2024.
//

#pragma once

#include "../Math/Vector3.h"
#include "../Math/Ray.h"

struct AABB {
    Vector3 min, max;

    AABB() = default;
    AABB(const Vector3& min, const Vector3& max) : min(min), max(max) {}

    bool Hit(const Ray& ray, float tmin, float tmax) const {
        for (int i = 0; i < 3; i++) {
            float invD = 1.0f / ray.direction[i];
            float t0 = (min[i] - ray.origin[i]) * invD;
            float t1 = (max[i] - ray.origin[i]) * invD;
            if (invD < 0.0f)
                std::swap(t0, t1);

            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;

            if (tmax <= tmin)
                return false;
        }
        return true;
    }

    static AABB SurroundingBox(AABB b0, AABB b1) {
        Vector3 small(fminf(b0.min.x, b1.min.x), fminf(b0.min.y, b1.min.y), fminf(b0.min.z, b1.min.z));
        Vector3 large(fmaxf(b0.max.x, b1.max.x), fmaxf(b0.max.y, b1.max.y), fmaxf(b0.max.z, b1.max.z));

        return AABB(small, large);
    }
};
