//
// Created by Lucas Täkker on 14/05/2024.
//

#pragma once

#include "Vector3.h"

struct Ray {
    Ray() = default;
    Ray(const Vector3& origin, const Vector3& direction) {
        this->origin = origin;
        this->direction = direction;
    }

    Vector3 At(float t) const {
        return origin + t * direction;
    }

    Vector3 origin, direction;
};
